#ifndef EXtoMemREGISTER_H
#define EXtoMemREGISTER_H

#include "StageRegister.h"
#ifndef MEMORYSTORE_H
#define MEMORYSTORE_H
#include "MemoryStore.h"
#endif

class EXtoMemRegister : public StageRegister {
public:
    EXtoMemRegister();
    void SetRegWrite(bool RegWriteVal);
    void SetMemRead(bool MemReadVal);
    void SetMemWrite(bool MemWriteVal);
    void SetMemToReg(bool MemToRegVal);
    void SetBranch(bool BranchVal);
    void SetZero(bool ZeroVal);
    void SetALUResult(uint32_t ALUResultVal);
    void SetReadData2(uint32_t ReadData2Val);
    void SetDestination(uint8_t DesintationVal);
    void SetInstructionForDump(uint32_t InstructionVal);
    void SetMemSize(enum MemEntrySize size);

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
