#include "InstructionFetch.h"
#include "sim.h"
#include "Cache.h"

enum {UNKNOWN = 0xdeefdeef, HALT_INSTR = 0xfeedfeed};

extern Cache* ICache;
extern IFtoIDRegister* IFtoID;
extern IDtoExRegister* IDtoEX;

static uint32_t Instruction;
static uint32_t PC = 0;
static bool pleaseBranch = false;
static bool pcWrite = false;
static int32_t branchAddress;
static bool IF_halted = false;

void IF_pleaseBranch(int32_t  branchAddressVal){
    pleaseBranch = true;
    branchAddress = branchAddressVal;
}
void IF_setPCWrite(bool pcWriteVal){
    pcWrite = pcWriteVal;
}

void IF_unsetHalted() {
    IF_halted = false;
}

int runInstructionFetch(){
    if (IF_halted) {
        IFtoID->SetInstruction(0);
        setInstruction(0, 0);
        return 0;
    }

    // ID telling us to branch
    if (pcWrite) {
        if (pleaseBranch) {
            PC = branchAddress;
            pleaseBranch = false;
        } else {
            PC += 4;
        }
        printf("bad: %u\n", PC);
    } else {
        printf("good %u\n", PC);
    }

    /* grab + write the instruction address*/
    int ret = ICache->Read(PC, Instruction, WORD_SIZE);
    if (ret > 0) {
        setInstruction(0, UNKNOWN);
    } else {

        setInstruction(0, Instruction);
    }

    if (Instruction == HALT_INSTR) {
        IF_halted = true;
    }

    IFtoID->SetInstruction(Instruction);
    if (!pcWrite)
        printf("instr: %x\n", Instruction);

    /* passing along PC+4 to the decode stage of the next cycle so that
        we can accurately predit the branch prediction */
    IFtoID->SetPC(PC+4);
    return ret;
}
