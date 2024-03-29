/* -------------------------------------------------------------------------- */
/* MemToWBRegister.h                                                          */
/* Lachlan and Marie                                                          */
/* -------------------------------------------------------------------------- */

#include "MemToWBRegister.h"

MemToWBRegister::MemToWBRegister(){

}

/* -------------------------------------------------------------------------- */

void MemToWBRegister::SetRegWrite(bool RegWriteVal)
{
    tempRegWrite = RegWriteVal;
}
void MemToWBRegister::SetMemToReg(bool MemToRegVal)
{
    tempMemToReg = MemToRegVal;
}
void MemToWBRegister::SetMemoryOutput(uint32_t MemoryOutputVal)
{
    tempMemoryOutput = MemoryOutputVal;
}
void MemToWBRegister::SetALUResult(uint32_t ALUResultVal)
{
    tempALUResult = ALUResultVal;
}
void MemToWBRegister::SetDestination(uint8_t DesintationVal)
{
    tempDestination = DesintationVal;
}
void MemToWBRegister::SetInstructionForDump(uint32_t InstructionVal)
{
    tempInstruction = InstructionVal;
}

void MemToWBRegister::SetMemSize(enum MemEntrySize size)
{
    tempMemSize = size;
}

/* ------------------------------------------------------------------ */

bool MemToWBRegister::GetRegWrite() const
{
    return RegWrite;
}
bool MemToWBRegister::GetMemToReg() const
{
    return MemToReg;
}
uint32_t MemToWBRegister::GetMemoryOutput() const
{
    return MemoryOutput;
}
uint32_t MemToWBRegister::GetALUResult() const
{
    return ALUResult;
}
uint8_t MemToWBRegister::GetDestination() const
{
    return Destination;
}
uint32_t MemToWBRegister::GetInstructionForDump() const
{
    return Instruction;
}

enum MemEntrySize MemToWBRegister::GetMemSize() const
{
    return memSize;
}

/* ------------------------------------------------------------------ */

void MemToWBRegister::CommitValues()
{
    RegWrite = tempRegWrite;
    MemToReg = tempMemToReg;
    ALUResult = tempALUResult;
    MemoryOutput = tempMemoryOutput;
    Destination = tempDestination;
    Instruction = tempInstruction;
    memSize = tempMemSize;
}

/* ------------------------------------------------------------------ */
