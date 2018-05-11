#include "EXtoMemRegister.h"
/* ExToMem */
/*
    (1) RegWrite
    (2) MemWrite
    (3) MemRead
    (4) MemToReg
    (5) Branch
    (6) Zero (result on ALU?)
    (7) Branch Address --> 32
    (8) ALU result --> 32
    (9) ReadData2 --> 32
    (10) Destination --> 5
*/
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
void EXtoMemRegister::SetBranchAddress(uint32_t BranchAddressVal)
{
    tempBranchAddress = BranchAddressVal;
}
void EXtoMemRegister::SetReadData2(uint32_t ReadData2Val)
{
    tempReadData2 = ReadData2Val;
}
void EXtoMemRegister::SetDestination(uint8_t DesintationVal)
{
    tempDestination = DesintationVal;
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
uint32_t EXtoMemRegister::GetBranchAdress() const
{
    return BranchAddress;
}
uint32_t EXtoMemRegister::GetReadData2() const
{
    return ReadData2;
}
uint8_t EXtoMemRegister::GetDestination() const
{
    return Destination;
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
    BranchAddress = tempBranchAddress;
    ReadData2 = tempReadData2;
    Destination = tempDestination;
}

/* ------------------------------------------------------------------ */
