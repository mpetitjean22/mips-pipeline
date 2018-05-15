/* -------------------------------------------------------------------------- */
/* MemToWBRegister.h                                                          */
/* Lachlan and Marie                                                          */
/* Represents the MEM/WB Stage Register in DataPath                           */
/* -------------------------------------------------------------------------- */

#ifndef MemToWBREGISTER_H
#define MemToWBREGISTER_H

#include "StageRegister.h"
#ifndef MEMORYSTORE_H
#define MEMORYSTORE_H
#include "MemoryStore.h"
#endif

class MemToWBRegister : public StageRegister {
public:
    MemToWBRegister();

    /* sets the control line to 1 if the instruction will write to a register,
     otherwise set to 0 */
    void SetRegWrite(bool RegWriteVal);

    /* MemToReg is set to 1 if you are writing a value from memory to a register,
        otherwise it is set to 0 */
    void SetMemToReg(bool MemToRegVal);

    /* Contains the value that is received from memory according the address
        that was inputted */
    void SetMemoryOutput(uint32_t MemoryOutputVal);

    /* Contains the result of the ALU that is being passed along from the
        instruction's execution stage */
    void SetALUResult(uint32_t ALUResultVal);

    /* gives the register number where either MemoryOuput or ALUResult */
    void SetDestination(uint8_t DesintationVal);

    /* Sets the instruction to be pulled by the dumpPipeline so we know which Instruction
        is in which stage */
    void SetInstructionForDump(uint32_t InstructionVal);

    /* Sets the MemSize depending on the enum MemEntry size to be read or written
        to memory in the memory stage */
    void SetMemSize(enum MemEntrySize size);

    /* similar to above except the getter functions for the variable */
    bool GetRegWrite() const;
    bool GetMemToReg() const;
    uint32_t GetMemoryOutput() const;
    uint32_t GetALUResult() const;
    uint8_t GetDestination() const;
    uint32_t GetInstructionForDump() const;
    enum MemEntrySize GetMemSize() const;

    /* updates the previous version of the register with the new values of the register */
    void CommitValues();

private:
    bool MemToReg;
    bool RegWrite;
    uint32_t ALUResult;
    uint32_t MemoryOutput;
    uint8_t Destination;
    uint32_t Instruction;
    enum MemEntrySize memSize;

    bool tempMemToReg;
    bool tempRegWrite;
    uint32_t tempALUResult;
    uint32_t tempMemoryOutput;
    uint8_t tempDestination;
    uint32_t tempInstruction;
    enum MemEntrySize tempMemSize;
};

#endif
