#include "Decode.h"
#include "sim.h"

extern IDtoExRegister* IDtoEX;
extern IFtoIDRegister* IFtoID;
extern EXtoMemRegister* EXtoMEM;
extern MemToWBRegister* MEMtoWB;

extern Register_T regs;

static bool execptionJump = false;
static uint32_t Instruction;

enum OP_IDS
{
    //R-type opcodes...
    OP_ZERO = 0,
    //I-type opcodes...
    OP_ADDI = 0x8,
    OP_ADDIU = 0x9,
    OP_ANDI = 0xc,
    OP_BEQ = 0x4,
    OP_BNE = 0x5,
    OP_LBU = 0x24,
    OP_LHU = 0x25,
    OP_LUI = 0xf,
    OP_LW = 0x23,
    OP_ORI = 0xd,
    OP_SLTI = 0xa,
    OP_SLTIU = 0xb,
    OP_SB = 0x28,
    OP_SH = 0x29,
    OP_SW = 0x2b,
    //J-type opcodes...
    OP_J = 0x2,
    OP_JAL = 0x3
};
enum FUN_IDS
{
    FUN_ADD = 0x20,
    FUN_ADDU = 0x21,
    FUN_AND = 0x24,
    FUN_JR = 0x08,
    FUN_NOR = 0x27,
    FUN_OR = 0x25,
    FUN_SLT = 0x2a,
    FUN_SLTU = 0x2b,
    FUN_SLL = 0x00,
    FUN_SRL = 0x02,
    FUN_SUB = 0x22,
    FUN_SUBU = 0x23
};

static uint8_t getOpcode(uint32_t instr){
    return (uint8_t)((instr >> 26) & 0x3f);
}
static uint8_t getReadRegister1(uint32_t instr){
    return (uint8_t)((instr >> 21) & 0x1f);
}
static uint8_t getReadRegister2(uint32_t instr){
    return (uint8_t)((instr >> 16) & 0x1f);
}
static uint8_t getDest2(uint32_t instr){
    return (uint8_t)((instr >> 11) & 0x1f);
}
static uint16_t getImmediate(uint32_t instr){
    return instr & 0xffff;
}
static uint32_t somethingToSignExtend(uint16_t imm){
    uint32_t newMasked;
    if (((1 << 15) & imm) >> 15) {
        newMasked = (uint32_t)(0xFFFF0000 | imm);
    } else {
        newMasked = (uint32_t)(0x00000000 | imm);
    }
    return newMasked;
}

// helps with supporting the whole WB in first half of the cycle
// and the ID in the second half of the cycle
void redoRegisterRead(){
    uint32_t newRead1, newRead2;
    newRead1 = generalRegRead(regs, (int)getReadRegister1(Instruction));
    newRead2 = generalRegRead(regs, (int)getReadRegister2(Instruction));
    IDtoEX->SetReadData1(newRead1);
    IDtoEX->SetReadData2(newRead2);
}

static void writeControlLines(uint8_t opcode, uint8_t func){
    bool RegDst     = 0;
    bool ALUop1     = 0;
    bool ALUop2     = 0;
    bool ALUop3     = 0;
    bool ALUSrc     = 0;
    bool Branch     = 0;
    bool MemRead    = 0;
    bool MemWrite   = 0;
    bool RegWrite   = 0;
    bool MemToReg   = 0;
    bool Overflow   = 0;
    enum MemEntrySize memSize = WORD_SIZE;

    /* The Textbook's ALUops were not extensive enough to account for
        all of the instructions in the MIPS implementation. Thus, I have
        added a 3rd op line which follow the following:
                            op1     op2     op3
        Insrt. R-type       1       0       0
        LW + SW (add)       0       0       0
        BE (subtract)       0       1       0
        (or)                0       1       1
        (and)               0       0       1
        (SLT)               1       0       1
    */

    switch(opcode){
        case OP_ZERO:
            if(func == FUN_ADD || func == FUN_SUB){
                Overflow = 1;
            }
            RegDst      = 1;
            ALUop1      = 1;
            RegWrite    = 1;
            break;
        case OP_ADDI:
            Overflow    = 1;
            RegWrite    = 1;
            ALUSrc      = 1;
            break;
        case OP_ADDIU:
            RegWrite    = 1;
            ALUSrc      = 1;
            break;
        case OP_ANDI:
            RegWrite    = 1;
            ALUSrc      = 1;
            ALUop3      = 1;
            break;
        case OP_BEQ:
        case OP_BNE:
            // implement this!
            break;
        case OP_LBU:
            MemRead = 1;
            ALUSrc = 1;
            MemToReg = 1;
            RegWrite = 1;
            memSize = BYTE_SIZE;
            break;
        case OP_LHU:
            MemRead = 1;
            ALUSrc = 1;
            MemToReg = 1;
            RegWrite = 1;
            memSize = HALF_SIZE;
            break;
        case OP_LW:
            MemRead = 1;
            ALUSrc = 1;
            MemToReg = 1;
            RegWrite = 1;
            memSize = WORD_SIZE;
            break;
        case OP_LUI:
            break;
        case OP_ORI:
            RegWrite    = 1;
            ALUSrc      = 1;
            ALUop2      = 1;
            ALUop3      = 1;
            break;
        case OP_SLTI:
            RegWrite    = 1;
            ALUSrc      = 1;
            ALUop1      = 1;
            ALUop3      = 1;
            Overflow    = 1;
            break;
        case OP_SLTIU:
            RegWrite    = 1;
            ALUSrc      = 1;
            ALUop1      = 1;
            ALUop3      = 1;
            break;
        case OP_SB:
            ALUSrc = 1;
            MemWrite = 1;
            memSize = BYTE_SIZE;
            break;
        case OP_SH:
            ALUSrc = 1;
            MemWrite = 1;
            memSize = HALF_SIZE;
            break;
        case OP_SW:
            ALUSrc = 1;
            MemWrite = 1;
            memSize = WORD_SIZE;
            break;
        case OP_JAL:
            RegWrite = 1;
            break;
            execptionJump = true;
    //    default:
            // the instruction is not valid
            // (1) set the PC to 0x8000
            // (2) instruction becomes a NOP
            // (3) rest of the instructions become a NOP
    }

    IDtoEX->SetRegDst(RegDst);
    IDtoEX->SetALUop1(ALUop1);
    IDtoEX->SetALUop2(ALUop2);
    IDtoEX->SetALUop3(ALUop3);
    IDtoEX->SetALUSrc(ALUSrc);
    IDtoEX->SetBranch(Branch);
    IDtoEX->SetMemRead(MemRead);
    IDtoEX->SetMemWrite(MemWrite);
    IDtoEX->SetRegWrite(RegWrite);
    IDtoEX->SetMemToReg(MemToReg);
    IDtoEX->SetMemSize(memSize);
    IDtoEX->SetOverflow(Overflow);
}

int runDecode(){
    uint8_t opcode;
    uint8_t readRegister1;
    uint8_t readRegister2;
    uint8_t dest2;
    uint32_t immediateSE;

    //(1) Get the values we need from instruction
    Instruction     = IFtoID->GetInstruction();
    opcode          = getOpcode(Instruction);                      // 26 - 31 (opcode)
    readRegister1   = getReadRegister1(Instruction);               // 21 - 25 (RS)
    readRegister2   = getReadRegister2(Instruction);               // 16 - 20 (RT)
    dest2           = getDest2(Instruction);                       // 11 - 15 (RD)
    immediateSE     = somethingToSignExtend(
                        getImmediate(Instruction));                  // 0 - 15 --> 32 sign extended


    //(2) Write the values to ID/EX
    IDtoEX->SetPC(IFtoID->GetPC());
    IDtoEX->SetReadData1(generalRegRead(regs, (int)readRegister1));
    IDtoEX->SetReadData2(generalRegRead(regs, (int)readRegister2));
    IDtoEX->SetImmediateValue(immediateSE);
    IDtoEX->SetDest1(readRegister2);
    IDtoEX->SetDest2(dest2);
    IDtoEX->SetRS(readRegister1);

    // (3) Write the control Flags
    uint8_t funct = Instruction & 0x3f;
    writeControlLines(opcode, funct);

    // (4) Resolve Branch
    // (4.1) Check for BEQ instruction
    uint32_t src1 = generalRegRead(regs, (int)readRegister1);
    uint32_t src2 = generalRegRead(regs, (int)readRegister2);

    bool EXtoIDforward1 = false;
    bool EXtoIDforward2 = false;
    bool MEMtoIDforward1 = false;
    bool MEMtoIDforward2 = false;


        // do we need to stall? EX --> ID (after 1 stall)
        if(EXtoMEM->GetRegWrite() &&
            readRegister1 != 0 &&
            EXtoMEM->GetDestination() == readRegister1){
                EXtoIDforward1 = true;
                // after stalled:
                src1 = EXtoMEM->GetALUResult();
        }
        // load use MEM --> ID (after 2 stalls)
        else if(MEMtoWB->GetRegWrite() &&
                readRegister1!= 0 &&
                MEMtoWB->GetDestination() == readRegister1){
                MEMtoIDforward1 = true;
                // after stalled:
                if(MEMtoWB->GetMemToReg() == 1){
                    src1 = MEMtoWB->GetMemoryOutput();
                }
                else{
                    src1 = MEMtoWB->GetALUResult();
                }

        }

        if (EXtoMEM->GetRegWrite() &&
            readRegister2 != 0 &&
            EXtoMEM->GetDestination() == readRegister2){
                EXtoIDforward2 = true;
                // after the stall we can execute:
                src2 = EXtoMEM->GetALUResult();
        }
        else if(MEMtoWB->GetRegWrite() &&
                readRegister2!= 0 &&
                MEMtoWB->GetDestination() == readRegister2){
                MEMtoIDforward2 = true;
                // after stalled:
                if(MEMtoWB->GetMemToReg() == 1){
                    src2 = MEMtoWB->GetMemoryOutput();
                }
                else{
                    src2 = MEMtoWB->GetALUResult();
                }
        }

        if((MEMtoIDforward2 && EXtoIDforward1) ||
            (MEMtoIDforward1 && EXtoIDforward2) ||
            (EXtoIDforward1 || EXtoIDforward2)){

            IDtoEX->SetRegDst(false);
            IDtoEX->SetALUop1(false);
            IDtoEX->SetALUop2(false);
            IDtoEX->SetALUop3(false);
            IDtoEX->SetALUSrc(false);
            IDtoEX->SetBranch(false);
            IDtoEX->SetMemRead(false);
            IDtoEX->SetMemWrite(false);
            IDtoEX->SetRegWrite(false);
            IDtoEX->SetMemToReg(false);
            IDtoEX->SetOverflow(false);
            IDtoEX->SetPC(0);
            IDtoEX->SetReadData1(0);
            IDtoEX->SetReadData2(0);
            IDtoEX->SetImmediateValue(0);
            IDtoEX->SetDest1(0);
            IDtoEX->SetDest2(0);
            IDtoEX->SetRS(0);
            IDtoEX->SetInstructionForDump(0);

            IF_setPCWrite(false);

            return 1;
        }
        else if(MEMtoIDforward1 || MEMtoIDforward2){
            // stall twice
        }

    if(opcode == OP_BEQ){
        if(src1 == src2){
            IF_pleaseBranch((int32_t)(IFtoID->GetPC() + (immediateSE<<2)));
            IF_setPCWrite(true);
        }
    }
    else if(opcode == OP_BNE){
        if(src1 != src2){
            IF_pleaseBranch((int32_t)(IFtoID->GetPC() + (immediateSE<<2)));
            IF_setPCWrite(true);
        }
    }
    else if(opcode == OP_J){
        IF_pleaseBranch((int32_t)(IFtoID->GetPC() + (immediateSE<<2)));
        IF_setPCWrite(true);
    }
    else if(opcode == OP_J){
        IF_pleaseBranch((int32_t)(IFtoID->GetPC() + (immediateSE<<2)));
        IF_setPCWrite(true);
    }
    else if(opcode == OP_JAL){
        IF_pleaseBranch((int32_t)(IFtoID->GetPC() + (immediateSE<<2) + 4));
        IF_setPCWrite(true);
        IDtoEX->SetReadData1(IFtoID->GetPC()+4);
        IDtoEX->SetReadData2(0);
        IDtoEX->SetALUop1(0);
        IDtoEX->SetALUop2(0);
        IDtoEX->SetALUop3(0);
        IDtoEX->SetDest1(31);
    }
    else if(opcode == OP_ZERO){
        if((immediateSE & 0x3F) == FUN_JR){
            IF_pleaseBranch((int32_t)src1);
            IF_setPCWrite(true);
        }
    }
    else if(execptionJump){
        IDtoEX->SetRegDst(false);
        IDtoEX->SetALUop1(false);
        IDtoEX->SetALUop2(false);
        IDtoEX->SetALUop3(false);
        IDtoEX->SetALUSrc(false);
        IDtoEX->SetBranch(false);
        IDtoEX->SetMemRead(false);
        IDtoEX->SetMemWrite(false);
        IDtoEX->SetRegWrite(false);
        IDtoEX->SetMemToReg(false);
        IDtoEX->SetOverflow(false);
        IDtoEX->SetPC(0);
        IDtoEX->SetReadData1(0);
        IDtoEX->SetReadData2(0);
        IDtoEX->SetImmediateValue(0);
        IDtoEX->SetDest1(0);
        IDtoEX->SetDest2(0);
        IDtoEX->SetRS(0);
        IDtoEX->SetInstructionForDump(0);

        IFtoID->SetPC(0);
        IFtoID->SetInstruction(0);

        IF_pleaseBranch((int32_t)0x8000);
        IF_setPCWrite(true);
        IF_unsetHalted();
        execptionJump = false;
    }
    else{
        IF_setPCWrite(true);
    }

    // update the instruction position
    IDtoEX->SetInstructionForDump(IFtoID->GetInstruction());
    setInstruction(1,IFtoID->GetInstruction());
    return 0;
}
