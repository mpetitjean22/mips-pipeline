#include "IDtoExRegister.h"

/* IFtoEx Register */

IDtoExRegister::IDtoExRegister(){

}
void IDtoExRegister::SetRegDst(bool RegDestVal)
{
    tempRegDst = RegDestVal;
}
void IDtoExRegister::SetALUop1(bool ALUop1Val)
{
    tempALUop1 = ALUop1Val;
}
void IDtoExRegister::SetALUop2(bool ALUop2Val)
{
    tempALUop2 = ALUop2Val;
}
void IDtoExRegister::SetALUop3(bool ALUop3Val)
{
    tempALUop3 = ALUop3Val;
}
void IDtoExRegister::SetALUSrc(bool ALUSrcVal)
{
    tempALUSrc = ALUSrcVal;
}
void IDtoExRegister::SetBranch(bool BranchVal)
{
    tempBranch = BranchVal;
}
void IDtoExRegister::SetMemRead(bool MemReadVal)
{
    tempMemRead = MemReadVal;
}
void IDtoExRegister::SetMemWrite(bool MemWriteVal)
{
    tempMemWrite = MemWriteVal;
}
void IDtoExRegister::SetRegWrite(bool RegWriteVal)
{
    tempRegWrite = RegWriteVal;
}
void IDtoExRegister::SetMemToReg(bool MemToRegVal)
{
    tempMemToReg = MemToRegVal;
}
void IDtoExRegister::SetPC(uint32_t PCVal)
{
    tempPC = PCVal;
}
void IDtoExRegister::SetReadData1(uint32_t ReadData1Val)
{
    tempReadData1 = ReadData1Val;
}
void IDtoExRegister::SetReadData2(uint32_t ReadData2Val)
{
    tempReadData2 = ReadData2Val;
}
void IDtoExRegister::SetImmediateValue(uint32_t ImmediateValueVal)
{
    tempImmediateValue = ImmediateValueVal;
}
void IDtoExRegister::SetDestination(uint8_t DestVal)
{
    tempDest = DestVal;
}
void IDtoExRegister::SetRS(uint8_t RSVal)
{
    tempRS = RSVal;
}
void IDtoExRegister::SetInstructionForDump(uint32_t InstructionVal)
{
    tempInstruction = InstructionVal;
}

void IDtoExRegister::SetMemSize(enum MemEntrySize size)
{
    tempMemSize = size;
}
void IDtoExRegister::SetOverflow(bool OverflowVal){
    tempOverflow = OverflowVal;
}

/* ------------------------------------------------------------------ */

bool IDtoExRegister::GetRegDst() const
{
    return RegDst;
}
bool IDtoExRegister::GetALUop1() const
{
    return ALUop1;
}
bool IDtoExRegister::GetALUop2() const
{
    return ALUop2;
}
bool IDtoExRegister::GetALUop3() const
{
    return ALUop3;
}
bool IDtoExRegister::GetALUSrc() const
{
    return ALUSrc;
}
bool IDtoExRegister::GetBranch() const
{
    return Branch;
}
bool IDtoExRegister::GetMemRead() const
{
    return MemRead;
}
bool IDtoExRegister::GetMemWrite() const
{
    return MemWrite;
}
bool IDtoExRegister::GetRegWrite() const
{
    return RegWrite;
}
bool IDtoExRegister::GetMemToReg() const
{
    return MemToReg;
}
uint32_t IDtoExRegister::GetPC() const
{
    return PC;
}
uint32_t IDtoExRegister::GetReadData1() const
{
    return ReadData1;
}
uint32_t IDtoExRegister::GetReadData2() const
{
    return ReadData2;
}
uint32_t IDtoExRegister::GetImmediateValue() const
{
    return ImmediateValue;
}
uint8_t IDtoExRegister::GetDestination() const
{
    return Dest;
}
uint8_t IDtoExRegister::GetRS() const
{
    return RS;
}
uint32_t IDtoExRegister::GetInstructionForDump() const
{
    return Instruction;
}
bool IDtoExRegister::GetOverflow() const{
    return Overflow;
}

enum MemEntrySize IDtoExRegister::GetMemSize() const
{
    return memSize;
}



/* ------------------------------------------------------------------ */

void IDtoExRegister::CommitValues()
{
    RegDst = tempRegDst;
    ALUop1 = tempALUop1;
    ALUop2 = tempALUop2;
    ALUSrc = tempALUSrc;
    Branch = tempBranch;
    MemRead = tempMemRead;
    MemWrite = tempMemWrite;
    MemToReg = tempMemToReg;
    RegWrite = tempRegWrite;
    PC = tempPC;
    ReadData1 = tempReadData1;
    ReadData2 = tempReadData2;
    ImmediateValue = tempImmediateValue;
    Dest = tempDest;
    RS = tempRS;
    Instruction = tempInstruction;
    memSize = tempMemSize;
    Overflow = tempOverflow;
}

/* ------------------------------------------------------------------ */
