#include "sim.h"

extern IDtoExRegister* IDtoEX;
extern IFtoIDRegister* IFtoID;

static bool isJumpInstruction;
static uint32_t Instruction;

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


    //(2) Write the values to ID/EX
    IDtoEX->SetPC(IFtoID->GetPC());
    // IDtoEX.SetReadData1 = CALL TO REGISTER (readregister1)
    // IDtoEX.SetReadData2 = CALL TO REGISTER (readregister2)
    IDtoEX->SetImmediateValue(immediateSE);
    IDtoEX->SetDest1(readRegister2);
    IDtoEX->SetDest2(dest2);
    IDtoEX->SetRS(readRegister1);

    // Write the control Flags (hard coded for add)
    bool RegDst     = true;
    bool ALUop1     = true;
    bool ALUop2     = false;
    bool ALUSrc     = false;
    bool Branch     = false;
    bool MemRead    = false;
    bool MemWrite   = false;
    bool RegWrite   = true;
    bool MemToReg   = false;

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
