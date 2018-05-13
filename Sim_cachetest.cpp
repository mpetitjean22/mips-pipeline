#include "sim.h"
#include "Cache.h"
#ifndef MEMORYSTORE_H
#define MEMORYSTORE_H
#include "MemoryStore.h"
#endif
IDtoExRegister* IDtoEX;
MemToWBRegister* MEMtoWB;
EXtoMemRegister* EXtoMEM;
IFtoIDRegister* IFtoID;

Register_T regs;

int main(void){
    struct CacheConfig config = {32, 8, TWO_WAY_SET_ASSOC, 5};

    MemoryStore *mem = createMemoryStore();
    mem->setMemValue(0x0, 0x1, WORD_SIZE);
    mem->setMemValue(0x4, 0x1, WORD_SIZE);
    mem->setMemValue(0x8, 0x2, WORD_SIZE);
    mem->setMemValue(0xc, 0x3, WORD_SIZE);
    mem->setMemValue(0x10, 0x5, WORD_SIZE);
    mem->setMemValue(0x14, 0x8, WORD_SIZE);
    mem->setMemValue(0x18, 0xa, WORD_SIZE);
    mem->setMemValue(0x1c, 0xb, WORD_SIZE);
    mem->setMemValue(0x20, 0xd, WORD_SIZE);
    mem->setMemValue(0x24, 0x4, WORD_SIZE);
    mem->setMemValue(0x28, 0x7, WORD_SIZE);
    mem->setMemValue(0x2c, 0xf, WORD_SIZE);
    mem->setMemValue(0x30, 0x9, WORD_SIZE);
    mem->setMemValue(0x34, 0x11, WORD_SIZE);
    mem->printMemory(0x0, 0x38);
    Cache cash(config, mem);
    uint32_t val;
    mem->getMemValue(0x0, val, WORD_SIZE);
    printf("0:%u\n", val);
    uint32_t one = 0, two = 0, three = 0, four = 0;
    printf("%d\n", cash.Read(0, one, WORD_SIZE));
    printf("%u\t%u\t%u\t%u\n", one, two, three, four);
    mem->getMemValue(0x0, val, WORD_SIZE);
    printf("0:%u\n", val);
    printf("%d\n", cash.Read(8, two, WORD_SIZE));
    printf("%u\t%u\t%u\t%u\n", one, two, three, four);
    printf("%d\n", cash.Read(20, three, WORD_SIZE));
    printf("%u\t%u\t%u\t%u\n", one, two, three, four);
    printf("%d\n", cash.Read(36, four, WORD_SIZE));
    printf("%u\t%u\t%u\t%u\n", one, two, three, four);
    printf("%d\n", cash.Write(4, two, WORD_SIZE));
    printf("%u\t%u\t%u\t%u\n", one, two, three, four);
    printf("%d\n", cash.Write(16, two, WORD_SIZE));
    printf("%u\t%u\t%u\t%u\n", one, two, three, four);
    printf("%d\n", cash.Write(32, two, WORD_SIZE));
    printf("%u\t%u\t%u\t%u\n", one, two, three, four);
    printf("%d\n", cash.Write(48, one, WORD_SIZE));
    printf("%u\t%u\t%u\t%u\n", one, two, three, four);
    printf("%d\n", cash.Read(0, three, WORD_SIZE));
    printf("%u\t%u\t%u\t%u\n", one, two, three, four);
    mem->printMemory(0x0, 0x38);
    printf("%u\t%u\t%u\t%u\n", one, two, three, four);

    //make the registers for each of the stages
    int cycleNum = 0;
    IDtoEX = new IDtoExRegister;
    MEMtoWB = new MemToWBRegister;
    EXtoMEM = new EXtoMemRegister;
    IFtoID = new IFtoIDRegister;
    RegisterInfo reg;
    regs = newReg();

    generalRegWrite(regs, 8, (uint32_t)6);
    generalRegWrite(regs, 9, (uint32_t)7);

    for(int i =0; i<5; i++){
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
    convertToRegInfo(regs, &reg);
    dumpRegisterState(reg);

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
