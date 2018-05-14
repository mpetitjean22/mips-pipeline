#include "Decode.h"
#include "sim.h"

extern IDtoExRegister* IDtoEX;
extern IFtoIDRegister* IFtoID;
extern Register_T regs;

static bool isJumpInstruction;
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
            RegDst      = 1;
            ALUop1      = 1;
            RegWrite    = 1;
            break;
        case OP_ADDI:
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
        case OP_J:
        case OP_JAL:
            // implement this!!
            break;
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
}
void runDecode(){
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

    /*printf("Instruction: %d \n", (int)Instruction);
    printf("opcode: %d \n", (int)opcode);
    printf("RS: %d \n", (int)readRegister1);
    printf("RT: %d \n", (int)readRegister2);
    printf("RD: %d \n", (int)dest2);
    */
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
    if(opcode == OP_BEQ){
        // check to see if the two are actually equal (needs to branch)
        if(generalRegRead(regs, (int)readRegister1) == generalRegRead(regs, (int)readRegister2)){
            IF_pleaseBranch((int32_t)(IFtoID->GetPC() + (immediateSE<<2)));
        }
    }
    else if(opcode == OP_BNE){
        if(generalRegRead(regs, (int)readRegister1) != generalRegRead(regs, (int)readRegister2)){
            IF_pleaseBranch((int32_t)(IFtoID->GetPC() + (immediateSE<<2)));
        }
    }
    else{
        IF_setPCWrite(true);
    }

    // update the instruction position
    IDtoEX->SetInstructionForDump(IFtoID->GetInstruction());
    setInstruction(1,IFtoID->GetInstruction());
}
