#include <stdio.h>

/* IFtoID Register */
/*
    (1) PC --> 32
    (2) Instruction --> 32
*/
uint32_t PC;
uint32_t Instruction;

uint32_t tempPC;
uint32_t tempInstruction;

void uint32_t setPC(uint32_t PCVal, int real){
    if(real){
        uint32_t PC = PCval;
    }
    else{
        uint32_t tempPC = PCval;
    }
}

void uint32_t setInstruction(uint32_t InstructionVal, int real){
    if(real){
        uint32_t Instruction = InstructionVal;
    }
    else{
        uint32_t tempInstruction = InstructionVal;
    }
}

void updateRealValues(){
    PC = tempPC;
    Instruction = tempInstruction;

    tempPC = 0;
    Instruction = 0;
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
