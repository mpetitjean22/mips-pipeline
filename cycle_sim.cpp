/* -------------------------------------------------------------------------- */
/* cycle_sim.cpp                                                              */
/* Lachlan and Marie                                                          */
/* Similates the Data path given by the textbook                              */
/* -------------------------------------------------------------------------- */

#include "sim.h"
#include "DriverFunctions.h"
#define CACHECONFIG_H
#include "Cache.h"

// TODO: fix lack of include guard quick fix


IDtoExRegister* IDtoEX;
MemToWBRegister* MEMtoWB;
EXtoMemRegister* EXtoMEM;
IFtoIDRegister* IFtoID;
Cache *ICache;
Cache *DCache;
MemoryStore *mem;

enum {HALT_INSTR = 0xfeedfeed, IF=0, ID=1, EX=2, Mem=3, WB=4};
static int cycleNum = 0;
static uint32_t stageInstruction[5] = {0,0,0,0,0};
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
    mem = mainMem;

    cycleNum = -1;
    return 0; // unused
}

int runCycles(uint32_t cycles)
{
    int ifStall, stalls, cyclesLeft, possibleStalls;
    uint32_t i;
    int icStall = ICache->StallCyclesHavePassed(0); // 0 to just get the amount left
    int dcStall = DCache->StallCyclesHavePassed(0);

    for(i = 0; i < cycles; i++) {
        if (icStall > 0 || dcStall > 0) {
            stalls = (icStall > dcStall) ? icStall : dcStall;
            cyclesLeft = cycles - i;
            possibleStalls = (stalls < cyclesLeft) ? stalls : cyclesLeft;
            icStall = ICache->StallCyclesHavePassed(possibleStalls);
            dcStall = DCache->StallCyclesHavePassed(possibleStalls);
            i += possibleStalls - 1; // avoid the increment
            cycleNum += possibleStalls;
            continue;
        }

        icStall = runInstructionFetch();
        runWriteBack();
        ifStall = runDecode();
        runExecute();
        dcStall = runMemory();

        if (!ifStall) {
            IFtoID->CommitValues();
        }
        IDtoEX->CommitValues();
        EXtoMEM->CommitValues();
        MEMtoWB->CommitValues();
        cycleNum++;

        if (stageInstruction[WB] == HALT_INSTR)
            break;
    }

    PipeState state;

    makePipeState(&state);
    dumpPipeState(state);

    return i < cycles - 1;
}

int runTillHalt()
{
    int icStall, dcStall, ifStall, stalls;

    icStall = ICache->StallCyclesHavePassed(0); // 0 to just get the amount left
    dcStall = DCache->StallCyclesHavePassed(0);

    while (1) {
        if (icStall > 0 || dcStall > 0) {
            stalls = (icStall > dcStall) ? icStall : dcStall;
            icStall = ICache->StallCyclesHavePassed(stalls);
            dcStall = DCache->StallCyclesHavePassed(stalls);
            cycleNum += stalls;
            continue;
        }

        icStall = runInstructionFetch();
        runWriteBack();
        ifStall = runDecode();
        runExecute();
        dcStall = runMemory();

        if (!ifStall) {
            IFtoID->CommitValues();
        }
        IDtoEX->CommitValues();
        EXtoMEM->CommitValues();
        MEMtoWB->CommitValues();
        cycleNum++;

        if (stageInstruction[WB] == HALT_INSTR)
            break;
    }

    PipeState state;

    makePipeState(&state);
    dumpPipeState(state);

    // run program until halt is received
    return 0; // unused
}

int finaliseSimulator() {
    struct SimulationStats stats;
    RegisterInfo reginfo;
    stats.totalCycles = cycleNum;
    stats.icHits = ICache->GetHits();
    stats.icMisses = ICache->GetMisses();
    stats.dcHits = DCache->GetHits();
    stats.dcMisses = DCache->GetMisses();
    printSimStats(stats);
    DCache->WriteAllDirtyToMain();

    convertToRegInfo(regs, &reginfo);
    dumpRegisterState(reginfo);
    dumpMemoryState(mem);

    return 0;
}
