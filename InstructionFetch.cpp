#include "InstructionFetch.h"
#include "sim.h"

extern IFtoIDRegister* IFtoID;
static uint32_t Instruction;
static uint32_t PC = 0;

/* my imaginary instruction cache */
static uint32_t getSomething(uint32_t PCVal){
    if(PCVal == 0){
        return (uint32_t)0x1285020;
    }
    else if(PCVal == 4){
        return (uint32_t)0x18B6820;
    }
    else if(PCVal == 8){
        return (uint32_t)0x1AA7020;
    }
    else if(PCVal == 12){
        return (uint32_t)0x1CA7820;
    }

}

void runInstructionFetch(){

    /* grab + write the instruction address*/
    Instruction = getSomething(PC);
    IFtoID->SetInstruction(Instruction);

    /* Tell the next stage which instruction num its working on */
    setCurrentInstructionNum(1, PC/4);

    /* Update + write the new PC */
    PC = PC + 4;
    IFtoID->SetPC(PC);
    setCurrentInstructionNum(0, PC/4);
}
