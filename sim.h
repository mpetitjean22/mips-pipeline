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

void setInstruction(int stage, uint32_t InstructionVal);
#endif
