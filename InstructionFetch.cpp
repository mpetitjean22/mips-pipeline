#include "InstructionFetch.h"
#include "sim.h"

extern IFtoIDRegister* IFtoID;
static uint32_t Instruction;
static uint32_t PC = 0;


static uint32_t getSomething(uint32_t PCVal){
    return (uint32_t)10;
}

void runInstructionFetch(IFtoIDRegister *IFtoID){

    /* grab + write the instruction address*/
    Instruction = getSomething(PC);
    IFtoID->SetInstruction(Instruction);

    /* Tell the next stage which instruction num its working on */
    setCurrentInstructionNum(1, PC/4);

    /* Update + write the new PC */
    PC = PC + 4;
    IFtoID->SetPC(PC);
}
