/* -------------------------------------------------------------------------- */
/*  sim.h                                                                     */
/* -------------------------------------------------------------------------- */

#ifndef SIM_H
#define SIM_H

#include <stdio.h>
#include <inttypes.h>
#include "IFtoIDRegister.h"
#include "MemToWBRegister.h"
#include "EXtoMemRegister.h"
#include "IDtoExRegister.h"
#include "InstructionFetch.h"
#include "Decode.h"
#include "Execute.h"
#include "Memory.h"
#include "WriteBack.h"
#include "register.h"

/* sets the instruction of the stage where int stage is:
    (0) if in IF
    (1) if in ID
    (2) if in EX
    (3) if in MEM
    (4) if in WB
*/
void setInstruction(int stage, uint32_t InstructionVal);

#endif
