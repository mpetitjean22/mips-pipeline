#include "Memory.h"
#include "sim.h"

extern MemToWBRegister* MEMtoWB;
extern EXtoMemRegister* EXtoMEM;

void runMemory(){
    MEMtoWB->SetRegWrite(EXtoMEM->GetRegWrite());
    MEMtoWB->SetMemToReg(EXtoMEM->GetMemToReg());
    MEMtoWB->SetALUResult(EXtoMEM->GetALUResult());
    MEMtoWB->SetDestination(EXtoMEM->GetDestination());

    uint32_t address = EXtoMEM->GetALUResult();
    uint32_t data = EXtoMEM->GetReadData2();


    MEMtoWB->SetInstructionForDump(EXtoMEM->GetInstructionForDump());
    setInstruction(3, EXtoMEM->GetInstructionForDump());
}
