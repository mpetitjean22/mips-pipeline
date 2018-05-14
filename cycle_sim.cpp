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

    cycleNum = 0;
    return 0; // unused
}

int runCycles(uint32_t cycles)
{
    int icStall, idStall, ifStall;
    for(uint32_t i = 0; i < cycles; i++) {
        icStall = runInstructionFetch();
        runWriteBack();
        ifStall = runDecode();
        runExecute();
        idStall = runMemory();

        if(ifStall){
            IFtoID->CommitValues();
        }
        IDtoEX->CommitValues();
        EXtoMEM->CommitValues();
        MEMtoWB->CommitValues();

        // need to check for halt instruction in WB and return 1 if it occurs
        cycleNum++;
        ifStall = 0;
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
