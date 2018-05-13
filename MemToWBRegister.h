#ifndef MemToWBREGISTER_H
#define MemToWBREGISTER_H

#include "StageRegister.h"

class MemToWBRegister : public StageRegister {
public:
    MemToWBRegister();
    void SetRegWrite(bool RegWriteVal);
    void SetMemToReg(bool MemToRegVal);
    void SetMemoryOutput(uint32_t MemoryOutputVal);
    void SetALUResult(uint32_t ALUResultVal);
    void SetDestination(uint8_t DesintationVal);
    void SetInstructionForDump(uint32_t InstructionVal);

    bool GetRegWrite() const;
    bool GetMemToReg() const;
    uint32_t GetMemoryOutput() const;
    uint32_t GetALUResult() const;
    uint8_t GetDestination() const;
    uint32_t GetInstructionForDump() const;

    void CommitValues();

private:
    bool MemToReg;
    bool RegWrite;
    uint32_t ALUResult;
    uint32_t MemoryOutput;
    uint8_t Destination;
    uint32_t Instruction;

    bool tempMemToReg;
    bool tempRegWrite;
    uint32_t tempALUResult;
    uint32_t tempMemoryOutput;
    uint8_t tempDestination;
    uint32_t tempInstruction;

};

#endif
