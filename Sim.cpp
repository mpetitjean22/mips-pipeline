// simulator stuff???
/*
#include "IDtoExRegister.h"
#include "IFtoIDRegister.h"
#include "EXtoMemRegister.h"
#include "MemToWBRegister"
*/

#include "sim.h"

int main(void){
    //make the registers for each of the stages

    IDtoExRegister* IDtoEX = new IDtoExRegister;
    MemToWBRegister* MEMtoWB = new MemToWBRegister;
    EXtoMemRegister* EXtoMEM = new EXtoMemRegister;
    IFtoIDRegister* IFtoID = new IFtoIDRegister;

    runInstructionFetch(IFtoID);

    // start the cycling process
    printf("HII THIS WORKS I HOPE IDKK \n");
    return 0;
}
// helps us keep track of which PC (instruction) is in
// each stage
int Current[5] = {-1, -1, -1, -1, -1};
int tempCurrent[5] = {-1, -1, -1, -1, -1};

int getCurrentInstructionNum(int Stage){
    return Current[Stage];
}
void setCurrentInstructionNum(int Stage, uint32_t Num){
    tempCurrent[Stage] = (int)Num;
}
