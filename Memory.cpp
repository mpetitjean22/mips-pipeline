#include "Memory.h"
#include "sim.h"
#include "Cache.h"

extern MemToWBRegister* MEMtoWB;
extern EXtoMemRegister* EXtoMEM;
extern Cache *DCache;

int runMemory(){
    int ret = 0;
    MEMtoWB->SetRegWrite(EXtoMEM->GetRegWrite());
    MEMtoWB->SetMemToReg(EXtoMEM->GetMemToReg());
    MEMtoWB->SetALUResult(EXtoMEM->GetALUResult());
    MEMtoWB->SetDestination(EXtoMEM->GetDestination());
    MEMtoWB->SetMemSize(EXtoMEM->GetMemSize()); // TODO: unnecessary maybe?

    uint32_t address = EXtoMEM->GetALUResult();
    if (EXtoMEM->GetMemWrite()) {
        uint32_t data = EXtoMEM->GetReadData2();
        enum MemEntrySize size = EXtoMEM->GetMemSize();
        ret = DCache->Write(address, data, size);
    } else if (EXtoMEM->GetMemRead()) {
        uint32_t data;
        enum MemEntrySize size = EXtoMEM->GetMemSize();
        ret = DCache->Read(address, data, size);
        MEMtoWB->SetMemoryOutput(data);
    }

    MEMtoWB->SetInstructionForDump(EXtoMEM->GetInstructionForDump());
    setInstruction(3, EXtoMEM->GetInstructionForDump());
    return ret;
}
