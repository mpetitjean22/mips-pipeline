#include "sim.h"
#include "Cache.h"

IDtoExRegister* IDtoEX;
MemToWBRegister* MEMtoWB;
EXtoMemRegister* EXtoMEM;
IFtoIDRegister* IFtoID;
Cache *ICache;
Cache *DCache;

static int cycleNum = 0;
static uint32_t WriteBackInstruction;
Register_T regs;

int main(void){
    //make the registers for each of the stages
    int cycleNum = 0;
    IDtoEX = new IDtoExRegister;
    MEMtoWB = new MemToWBRegister;
    EXtoMEM = new EXtoMemRegister;
    IFtoID = new IFtoIDRegister;
    RegisterInfo reginfo;
    regs = newReg();

    generalRegWrite(regs, 8, (uint32_t)11);
    generalRegWrite(regs, 9, (uint32_t)20);
    generalRegWrite(regs, 10, (uint32_t)30);
    generalRegWrite(regs, 11, (uint32_t)40);
    generalRegWrite(regs, 12, (uint32_t)50);
    generalRegWrite(regs, 13, (uint32_t)60);
    generalRegWrite(regs, 14, (uint32_t)70);

    for(int i =0; i<9; i++){
        runInstructionFetch();
        runDecode();
        runExecute();
        runMemory();
        runWriteBack();

        IFtoID->CommitValues();
        IDtoEX->CommitValues();
        EXtoMEM->CommitValues();
        MEMtoWB->CommitValues();
    }
    convertToRegInfo(regs, &reginfo);
    dumpRegisterState(reginfo);

    // start the cycling process
    printf("HII THIS WORKS I HOPE IDKK \n");

    return 0;
}
// helps us keep track of which PC (instruction) is in
// each stage

void setWriteBackInstruction(uint32_t InstructionVal){
    WriteBackInstruction = InstructionVal;
}
// should be called after the values to the stage registers have been commited
static void makePipeState(PipeState *state) {
    state->cycle = cycleNum;
    state->ifInstr = IFtoID->GetInstruction();
    state->idInstr = IDtoEX->GetInstructionForDump();
    state->exInstr = EXtoMEM->GetInstructionForDump();
    state->memInstr = MEMtoWB->GetInstructionForDump();
    state->wbInstr = WriteBackInstruction;
}
int initSimulator(CacheConfig & icConfig, CacheConfig & dcConfig, MemoryStore *mainMem)
{
    ICache = new Cache(icConfig, mainMem);
    DCache = new Cache(dcConfig, mainMem);
    IDtoEX = new IDtoExRegister;
    MEMtoWB = new MemToWBRegister;
    EXtoMEM = new EXtoMemRegister;
    IFtoID = new IFtoIDRegister;
    regs = newReg();
    cycleNum = 0;
    return 0; // unused
}

int runCycles(uint32_t cycles)
{
    for(uint32_t i = 0; i < cycles; i++) {
        runInstructionFetch();
        runWriteBack();
        runDecode();
        runExecute();
        runMemory();

        IFtoID->CommitValues();
        IDtoEX->CommitValues();
        EXtoMEM->CommitValues();
        MEMtoWB->CommitValues();

        // need to check for halt instruction in WB and return 1 if it occurs
        cycleNum++;

        updateCurrentInstructionNum();
    }

    // we should be using dumppiplinestate instead
    printf("Cycle: %d \n", cycleNum);
    printCurrent();

    return 0;
}

int runTillHalt()
{

    // run program until halt is received
    return 0; // unused
}

int finaliseSimulator() {
    // needs to be implemented
    return 0;
}
