/* -------------------------------------------------------------------------- */
/* IFtoIDRegister.h                                                           */
/* Lachlan and Marie                                                          */
/* Represents the IF/ID Stage Register in DataPath                            */
/* -------------------------------------------------------------------------- */

#ifndef IFtoIDREGISTER_H
#define IFtoIDREGISTER_H

#include "StageRegister.h"
#include <inttypes.h>

class IFtoIDRegister : public StageRegister {
public:
    IFtoIDRegister();

    /* sets the values to the values of PC */
    void SetPC(uint32_t PCVal);

    /* sets the Instruction value of the current Instruction associated with the stage */
    void SetInstruction(uint32_t InstructionVal);

    /* getter functions for the setters */
    uint32_t GetPC() const;
    uint32_t GetInstruction() const;

    void CommitValues();

private:
    uint32_t PC;
    uint32_t Instruction;
    uint32_t tempPC;
    uint32_t tempInstruction;
};

#endif
