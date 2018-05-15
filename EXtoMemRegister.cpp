/* -------------------------------------------------------------------------- */
/* EXtoMemRegister.cpp                                                        */
/* Lachlan and Marie                                                          */
/* Represents the EX/MEM Stage Register in DataPath                           */
/* -------------------------------------------------------------------------- */

#include "EXtoMemRegister.h"

EXtoMemRegister::EXtoMemRegister(){

}
void EXtoMemRegister::SetRegWrite(bool RegWriteVal)
{
    tempRegWrite = RegWriteVal;
}
void EXtoMemRegister::SetMemRead(bool MemReadVal)
{
    tempMemRead = MemReadVal;
}
void EXtoMemRegister::SetMemWrite(bool MemWriteVal)
{
    tempMemWrite = MemWriteVal;
}
void EXtoMemRegister::SetMemToReg(bool MemToRegVal)
{
    tempMemToReg = MemToRegVal;
}
void EXtoMemRegister::SetBranch(bool BranchVal)
{
    tempBranch = BranchVal;
}
void EXtoMemRegister::SetZero(bool ZeroVal)
{
    tempZero = ZeroVal;
}
void EXtoMemRegister::SetALUResult(uint32_t ALUResultVal)
{
    tempALUResult = ALUResultVal;
}
void EXtoMemRegister::SetReadData2(uint32_t ReadData2Val)
{
    tempReadData2 = ReadData2Val;
}
void EXtoMemRegister::SetDestination(uint8_t DesintationVal)
{
    tempDestination = DesintationVal;
}
void EXtoMemRegister::SetInstructionForDump(uint32_t InstructionVal)
{
    tempInstruction = InstructionVal;
}

void EXtoMemRegister::SetMemSize(enum MemEntrySize size)
{
    tempMemSize = size;
}

/* ------------------------------------------------------------------ */

bool EXtoMemRegister::GetRegWrite() const
{
    return RegWrite;
}
bool EXtoMemRegister::GetMemRead() const
{
    return MemRead;
}
bool EXtoMemRegister::GetMemWrite() const
{
    return MemWrite;
}
bool EXtoMemRegister::GetMemToReg() const
{
    return MemToReg;
}
bool EXtoMemRegister::GetBranch() const
{
    return Branch;
}
bool EXtoMemRegister::GetZero() const
{
    return Zero;
}
uint32_t EXtoMemRegister::GetALUResult() const
{
    return ALUResult;
}
uint32_t EXtoMemRegister::GetReadData2() const
{
    return ReadData2;
}
uint8_t EXtoMemRegister::GetDestination() const
{
    return Destination;
}
uint32_t EXtoMemRegister::GetInstructionForDump() const
{
    return Instruction;
}

enum MemEntrySize EXtoMemRegister::GetMemSize() const
{
    return memSize;
}


/* ------------------------------------------------------------------ */

void EXtoMemRegister::CommitValues()
{
    RegWrite = tempRegWrite;
    MemRead = tempMemRead;
    MemWrite = tempMemWrite;
    MemToReg = tempMemToReg;
    Branch = tempBranch;
    Zero = tempZero;
    ALUResult = tempALUResult;
    ReadData2 = tempReadData2;
    Destination = tempDestination;
    Instruction = tempInstruction;
    memSize = tempMemSize;
}

/* ------------------------------------------------------------------ */
