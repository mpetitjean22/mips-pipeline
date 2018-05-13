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
    OP_ZERO = 0
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
    bool ALUSrc     = 0;
    bool Branch     = 0;
    bool MemRead    = 0;
    bool MemWrite   = 0;
    bool RegWrite   = 0;
    bool MemToReg   = 0;

    // R-Type Instructions
    if(opcode == OP_ZERO){
        switch(func){
            case FUN_ADD:
                RegDst = 1;
                ALUop1 = 1;
                RegWrite = 1;
                break;
        }
    }

    IDtoEX->SetRegDst(RegDst);
    IDtoEX->SetALUop1(ALUop1);
    IDtoEX->SetALUop2(ALUop2);
    IDtoEX->SetALUSrc(ALUSrc);
    IDtoEX->SetBranch(Branch);
    IDtoEX->SetMemRead(MemRead);
    IDtoEX->SetMemWrite(MemWrite);
    IDtoEX->SetRegWrite(RegWrite);
    IDtoEX->SetMemToReg(MemToReg);
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

    // Write the control Flags (hard coded for add)
    uint8_t funct = Instruction & 0x3f;
    writeControlLines(opcode, funct);

    // update the instruction position
    setCurrentInstructionNum(2, getCurrentInstructionNum(1));
}
