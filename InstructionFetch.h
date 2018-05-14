#ifndef INSTRUCTIONFETCH_H
#define INSTRUCTIONFETCH_H

#include <inttypes.h>
#include "sim.h"

int runInstructionFetch();
void IF_pleaseBranch(int32_t  branchAddressVal);
void IF_setPCWrite(bool pcWriteVal);
#endif
