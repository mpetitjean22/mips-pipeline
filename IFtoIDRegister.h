#ifndef IFtoIDREGISTER_H
#define IFtoIDREGISTER_H

#include "Register.h"

class IFtoIDRegister : public Register {
public:
    IFtoIDRegister();
    void SetPC(uint32_t PCVal);
    void SetInstruction(uint32_t InstructionVal);
    uint32_t GetPC(void) const;
    uint32_t GetInstruction(void) const;
    void CommitValues(void);

private:
    uint32_t PC;
    uint32_t Instruction;
    uint32_t tempPC;
    uint32_t tempInstruction;
};

#endif
