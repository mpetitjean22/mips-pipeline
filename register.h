/* -------------------------------------------------------------------------- */
/* register.h                                                                 */
/* -------------------------------------------------------------------------- */

#ifndef REGISTER_INCLUDED
#define REGISTER_INCLUDED

#include <stdint.h>

#ifndef REGISTERINFO_INCLUDED
#define REGISTERINFO_INCLUDED
#include "RegisterInfo.h"
#endif

#define NUM_REGS 32

/* creates a struct to hold each of the register values */
typedef struct Register *Register_T;

/* takes in a struct regs, and a register number num, as well as a value, and
    writes the value to that register number in regs */
void generalRegWrite(Register_T regs, int num, uint32_t value);

/* reads the value stored in the register num in the regs struct */
uint32_t generalRegRead(Register_T regs, int num);

/* converts our struct to hold the register value to the given RegisterInfo
    files that we were given */
void convertToRegInfo(Register_T regs, RegisterInfo *reg);

/* initializes a new Register_T */
Register_T newReg(void);

/* writes to the pc register of regs */
void pcRegWrite(Register_T regs, uint32_t npc);

/* returns the value of the pc of regs */
uint32_t pcRegRead(Register_T regs);

/* increments the pc by 4 of regs */
void pcIncrementFour(Register_T regs);

#endif
