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

int getCurrentInstructionNum(int Stage);
void setCurrentInstructionNum(int Stage, uint32_t PCVal);
void updateCurrentInstructionNum();
void printCurrent();
#endif
