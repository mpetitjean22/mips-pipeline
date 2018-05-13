#include "WriteBack.h"
#include "sim.h"

extern Register_T regs;
extern MemToWBRegister* MEMtoWB;

void runWriteBack()
{
    if (MEMtoWB->GetRegWrite()) {
        generalRegWrite(regs, (int)MEMtoWB->GetDestination(), MEMtoWB->GetALUResult());
    }
    setInstruction(4, MEMtoWB->GetInstructionForDump()); 
    redoRegisterRead();
}
