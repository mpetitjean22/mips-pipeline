/* -------------------------------------------------------------------------- */
/* EXtoMemRegister.h                                                          */
/* Lachlan and Marie                                                          */
/* Represents the EX/MEM Stage Register in DataPath                           */
/* -------------------------------------------------------------------------- */

#ifndef EXtoMemREGISTER_H
#define EXtoMemREGISTER_H

#include "StageRegister.h"
#ifndef MEMORYSTORE_H
#define MEMORYSTORE_H
#include "MemoryStore.h"
#endif

class EXtoMemRegister : public StageRegister {
public:
    // contructor for the class
    EXtoMemRegister();

    /* sets the control line to 1 if the instruction will write to a register,
     otherwise set to 0 */
    void SetRegWrite(bool RegWriteVal);

    /* MemRead is set to 1 if the instruction reads from memory, otherwise 0 */
    void SetMemRead(bool MemReadVal);

    /* MemWrite is set to 1 if the instruction writes to memory, otherwise 0 */
    void SetMemWrite(bool MemWriteVal);

    /* MemToReg is set to 1 if you are writing a value from memory to a register,
        otherwise it is set to 0 */
    void SetMemToReg(bool MemToRegVal);

    /* Set branch is set to 1 if it is a branch instruction */
    void SetBranch(bool BranchVal);

    /* Set zero is set to 1 if the result from the ALU is 0, otherwise it is 0 */
    void SetZero(bool ZeroVal);

    /* contains the result of the ALU in the execute stage */
    void SetALUResult(uint32_t ALUResultVal);

    /* contains the result of the second read register value */
    void SetReadData2(uint32_t ReadData2Val);

    /* sets the destination for the result of the ALU should be written to (which
        register needs to be written to rd or rt depending on the instruction) */
    void SetDestination(uint8_t DesintationVal);

    /* Sets the instruction to be pulled by the dumpPipeline so we know which Instruction
        is in which stage */
    void SetInstructionForDump(uint32_t InstructionVal);

    /* Sets the MemSize depending on the enum MemEntry size to be read or written
        to memory in the memory stage */
    void SetMemSize(enum MemEntrySize size);

    /* similar to above, but the return values of what is currently in the register */
    bool GetRegWrite() const;
    bool GetMemRead() const;
    bool GetMemWrite() const;
    bool GetMemToReg() const;
    bool GetBranch() const;
    bool GetZero() const;
    uint32_t GetALUResult() const;
    uint32_t GetReadData2() const;
    uint8_t GetDestination() const;
    uint32_t GetInstructionForDump() const;
    enum MemEntrySize GetMemSize() const;

    /* updates the previous version of the register with the new values of the register */
    void CommitValues();

private:
    bool RegWrite;
    bool MemRead;
    bool MemWrite;
    bool MemToReg;
    bool Branch;
    bool Zero;
    uint32_t ALUResult;
    uint32_t ReadData2;
    uint8_t Destination;
    uint32_t Instruction;
    enum MemEntrySize memSize;

    bool tempRegWrite;
    bool tempMemRead;
    bool tempMemWrite;
    bool tempMemToReg;
    bool tempBranch;
    bool tempZero;
    uint32_t tempALUResult;
    uint32_t tempReadData2;
    uint8_t tempDestination;
    uint32_t tempInstruction;
    enum MemEntrySize tempMemSize;
};

#endif
