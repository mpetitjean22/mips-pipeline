#include "Memory.h"
#include "sim.h"

extern MemToWBRegister* MEMtoWB;
extern EXtoMemRegister* EXtoMEM;

void runMemory(){
    MEMtoWB->SetRegWrite(EXtoMEM->GetRegWrite());
    MEMtoWB->SetMemToReg(EXtoMEM->GetMemToReg());
//    MEMtoWB->SetMemoryOutput = something!!
    MEMtoWB->SetALUResult(EXtoMEM->GetALUResult());
    MEMtoWB->SetDestination(EXtoMEM->GetDestination());
    MEMtoWB->SetInstruction(EXtoMEm->GetInstruction());
    
}
