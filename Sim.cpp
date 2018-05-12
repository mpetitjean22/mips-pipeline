#include "sim.h"

IDtoExRegister* IDtoEX;
MemToWBRegister* MEMtoWB;
EXtoMemRegister* EXtoMEM;
IFtoIDRegister* IFtoID;


int main(void){
    //make the registers for each of the stages
    int cycleNum = 0;
    IDtoEX = new IDtoExRegister;
    MEMtoWB = new MemToWBRegister;
    EXtoMEM = new EXtoMemRegister;
    IFtoID = new IFtoIDRegister;

    for(int i =0; i<7; i++){
        runInstructionFetch();
        runDecode();
        runExecute();
        runMemory();
        runWriteBack();

        IFtoID->CommitValues();
        IDtoEX->CommitValues();
        EXtoMEM->CommitValues();
        MEMtoWB->CommitValues();

        cycleNum++;
        updateCurrentInstructionNum();
        printf("Cycle: %d \n", cycleNum);
        printCurrent();
    }

    // start the cycling process
    printf("HII THIS WORKS I HOPE IDKK \n");

    return 0;
}
// helps us keep track of which PC (instruction) is in
// each stage
int Current[5] = {-1, -1, -1, -1, -1};
int tempCurrent[5] = {-1, -1, -1, -1, -1};
char words[5][4] = {"IF", "ID", "EX", "MEM", "WB"};

int getCurrentInstructionNum(int Stage){
    return Current[Stage];
}
void setCurrentInstructionNum(int Stage, uint32_t PCVal){
    tempCurrent[Stage] = (int)PCVal;
}
void updateCurrentInstructionNum(){
    int i;
    for(i=0; i<5; i++){
        Current[i] = tempCurrent[i];
        tempCurrent[i] = -1;
    }
}
void printCurrent(){
    int i;
    for(i=0; i<5; i++){
        printf("%s: %d \n", words[i],(int)Current[i]);
    }
    printf("\n");
}
