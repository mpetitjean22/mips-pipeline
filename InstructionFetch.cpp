#include "InstructionFetch.h"
#include "sim.h"
#include "Cache.h"

enum {UNKNOWN = 0xdeefdeef};

extern Cache* ICache;
extern IFtoIDRegister* IFtoID;
extern IDtoExRegister* IDtoEX;

static uint32_t Instruction;
static uint32_t PC = 0;
static bool pleaseBranch = false;
static bool pcWrite = false;
static int32_t branchAddress;

void IF_pleaseBranch(int32_t  branchAddressVal){
    pleaseBranch = true;
    branchAddress = branchAddressVal;
}
void IF_setPCWrite(bool pcWriteVal){
    pcWrite = pcWriteVal;
}

void runInstructionFetch(){
    // ID telling us to branch
    if (pleaseBranch) {
        PC = branchAddress;
        pleaseBranch = false;
    } else if (pcWrite) {
        PC += 4
    }

    /* grab + write the instruction address*/
    int ret = ICache.Read(PC, Instruction, WORD_SIZE);
    if (ret > 0) {
        IFtoID->
    }
    IFtoID->SetInstruction(Instruction);

    /* Update + write the new PC */
    IFtoID->SetPC(PC);

}
