#include "IFtoIDRegister.h"

/* IFtoID Register */
/*
    (1) PC --> 32
    (2) Instruction --> 32
*/
static uint32_t PC;
static uint32_t Instruction;

static uint32_t tempPC;
static uint32_t tempInstruction;

void setPC(uint32_t PCVal)
{
    tempPC = PCVal;
}

uint32_t getPC(void)
{
    return PC;
}

void setInstruction(uint32_t InstructionVal)
{
    tempInstruction = InstructionVal;
}

uint32_t getInstruction(void)
{
    return Instruction;
}

void commitValues(void)
{
    PC = tempPC;
    Instruction = tempInstruction;
}


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

/* MemToWB */
/*
    (1) MemToReg
    (2) RegWrite
    (3) MemoryOutput --> 32
    (4) Destination --> 5
    (5) ALUResult --> 32
*/
