#ifndef SIM_H
#define SIM_H

#include <stdio.h>
#include <inttypes.h>
#include "IFtoIDRegister.h"
#include "MemToWBRegister.h"
#include "EXtoMemRegister.h"
#include "IDtoExRegister.h"
#include "InstructionFetch.h"



int getCurrentInstructionNum(int Stage);
void setCurrentInstructionNum(int Stage, uint32_t Num);

#endif
