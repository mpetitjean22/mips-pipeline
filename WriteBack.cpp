#include "WriteBack.h"
#include "sim.h"

extern MemToWBRegister* MEMtoWB;

void runWriteBack()
{
    if (MEMtoWB->GetRegWrite()) {
        // write to ALUSrc to Destination!
    }
}
