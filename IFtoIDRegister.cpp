#include "IFtoIDRegister.h"

/* IFtoID Register */
/*
    (1) PC --> 32
    (2) Instruction --> 32
*/
/* ------------------------------------------------------------------ */

static uint32_t PC;
static uint32_t Instruction;

/* ------------------------------------------------------------------ */

static uint32_t tempPC;
static uint32_t tempInstruction;

/* ------------------------------------------------------------------ */

void setPC(uint32_t PCVal)
{
    tempPC = PCVal;
}
void setInstruction(uint32_t InstructionVal)
{
    tempInstruction = InstructionVal;
}

/* ------------------------------------------------------------------ */

uint32_t getPC(void)
{
    return PC;
}
uint32_t getInstruction(void)
{
    return Instruction;
}

/* ------------------------------------------------------------------ */

void commitValues(void)
{
    PC = tempPC;
    Instruction = tempInstruction;
}

/* ------------------------------------------------------------------ */
