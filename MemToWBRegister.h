#ifndef MemToWBREGISTER_H
#define MemToWBREGISTER_H

#include "Register.h"

class MemToWBRegister : public Register {
public:
    MemToWBRegister();
    void SetRegWrite(bool RegWriteVal);
    void SetMemToReg(bool MemToRegVal);
    void SetMemoryOutput(uint32_t MemoryOutputVal);
    void SetALUResult(uint32_t ALUResultVal);
    void SetDestination(uint8_t DesintationVal);
    bool GetRegWrite() const;
    bool GetMemToReg() const;
    uint32_t GetMemoryOutput() const;
    uint32_t GetALUResult() const;
    uint8_t GetDestination() const;
    void CommitValues();

private:
    bool MemToReg;
    bool RegWrite;
    uint32_t ALUResult;
    uint32_t MemoryOutput;
    uint8_t Destination;
    bool tempMemToReg;
    bool tempRegWrite;
    uint32_t tempALUResult;
    uint32_t tempMemoryOutput;
    uint8_t tempDestination;
};

#endif
