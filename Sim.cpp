// simulator stuff???
/*
#include "IDtoExRegister.h"
#include "IFtoIDRegister.h"
#include "EXtoMemRegister.h"
#include "MemToWBRegister"
*/
#include <stdio.h>
#include "IFtoIDRegister.h"
#include "MemToWBRegister.h"
#include "EXtoMemRegister.h"
#include "IDtoExRegister.h"


int main(void){
    //make the registers for each of the stages

    IDtoExRegister* IDtoEX = new IDtoExRegister;
    MemToWBRegister* MEMtoWB = new MemToWBRegister;
    EXtoMemRegister* EXtoMEM = new EXtoMemRegister;
    IFtoIDRegister* IFtoID = new IFtoIDRegister;

    // start the cycling process
    printf("HII THIS WORKS I HOPE IDKK \n");
    return 0;
}
