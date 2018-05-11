#include "IFtoIDRegister.h"

/* IFtoID Register */
/*
    (1) PC --> 32
    (2) Instruction --> 32
*/

void IFtoIDRegister::SetPC(uint32_t PCVal)
{
    tempPC = PCVal;
}
void IFtoIDRegister::SetInstruction(uint32_t InstructionVal)
{
    tempInstruction = InstructionVal;
}

/* ------------------------------------------------------------------ */

uint32_t IFtoIDRegister::GetPC() const
{
    return PC;
}
uint32_t IFtoIDRegister::GetInstruction() const
{
    return Instruction;
}

/* ------------------------------------------------------------------ */

void IFtoIDRegister::CommitValues()
{
    PC = tempPC;
    Instruction = tempInstruction;
}

/* ------------------------------------------------------------------ */
