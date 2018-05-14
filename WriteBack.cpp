#include "WriteBack.h"
#include "sim.h"

extern Register_T regs;
extern MemToWBRegister* MEMtoWB;

void runWriteBack()
{
    if (MEMtoWB->GetRegWrite()) {
        if (MEMtoWB->GetMemToReg())
            generalRegWrite(regs, (int)MEMtoWB->GetDestination(), MEMtoWB->GetMemoryOutput());
        else
            generalRegWrite(regs, (int)MEMtoWB->GetDestination(), MEMtoWB->GetALUResult());
    }
    setInstruction(4, MEMtoWB->GetInstructionForDump());
    //redoRegisterRead(); 
}
