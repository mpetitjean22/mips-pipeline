#include "sim.h"
#include "Cache.h"
#include "DriverFunctions.h"

IDtoExRegister* IDtoEX;
MemToWBRegister* MEMtoWB;
EXtoMemRegister* EXtoMEM;
IFtoIDRegister* IFtoID;
Cache *ICache;
Cache *DCache;
RegisterInfo reginfo;

static int cycleNum = 0;
static uint32_t stageInstruction[5] = {0,0,0,0,0};
static bool stalled;
Register_T regs;

/*int main(void){
    //make the registers for each of the stages
    int cycleNum = 0;
    IDtoEX = new IDtoExRegister;
    MEMtoWB = new MemToWBRegister;
    EXtoMEM = new EXtoMemRegister;
    IFtoID = new IFtoIDRegister;
    RegisterInfo reginfo;
    regs = newReg();

    MemoryStore *mem = createMemoryStore();
    CacheConfig icConfig;
    icConfig.cacheSize = 1024;
    icConfig.blockSize = 64;
    icConfig.type = DIRECT_MAPPED;
    icConfig.missLatency = 5;
    CacheConfig dcConfig = icConfig;
    ICache = new Cache(icConfig, mem);
    DCache = new Cache(dcConfig, mem);

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
*/

// helps us keep track of which PC (instruction) is in
// each stage
void setInstruction(int stage, uint32_t InstructionVal){
    stageInstruction[stage] = InstructionVal;
}

// should be called after the values to the stage registers have been commited
static void makePipeState(PipeState *state) {
    state->cycle = cycleNum;
    state->ifInstr = stageInstruction[0];
    state->idInstr = stageInstruction[1];
    state->exInstr = stageInstruction[2];
    state->memInstr = stageInstruction[3];
    state->wbInstr = stageInstruction[4];
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
    stalled = false;

    // temporary!
    generalRegWrite(regs, 8, (uint32_t)11);
    generalRegWrite(regs, 9, (uint32_t)20);
    generalRegWrite(regs, 10, (uint32_t)30);
    generalRegWrite(regs, 11, (uint32_t)40);
    generalRegWrite(regs, 12, (uint32_t)50);
    generalRegWrite(regs, 13, (uint32_t)60);
    generalRegWrite(regs, 14, (uint32_t)70);

    cycleNum = 0;
    return 0; // unused
}

int runCycles(uint32_t cycles)
{
    int icStall, idStall;
    for(uint32_t i = 0; i < cycles; i++) {
        icStall = runInstructionFetch();
        runWriteBack();
        runDecode();
        runExecute();
        idStall = runMemory();

        IFtoID->CommitValues();
        IDtoEX->CommitValues();
        EXtoMEM->CommitValues();
        MEMtoWB->CommitValues();

        // need to check for halt instruction in WB and return 1 if it occurs
        cycleNum++;
    }

    PipeState state;

    makePipeState(&state);
    convertToRegInfo(regs, &reginfo);

    dumpRegisterState(reginfo);
    dumpPipeState(state);
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
