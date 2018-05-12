#ifndef EXtoMemREGISTER_H
#define EXtoMemREGISTER_H

#include "StageRegister.h"

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
    void SetBranchAddress(uint32_t BranchAddressVal);
    void SetReadData2(uint32_t ReadData2Val);
    void SetDestination(uint8_t DesintationVal);

    bool GetRegWrite() const;
    bool GetMemRead() const;
    bool GetMemWrite() const;
    bool GetMemToReg() const;
    bool GetBranch() const;
    bool GetZero() const;
    uint32_t GetALUResult() const;
    uint32_t GetBranchAdress() const;
    uint32_t GetReadData2() const;
    uint8_t GetDestination() const;
    void CommitValues();

private:
    bool RegWrite;
    bool MemRead;
    bool MemWrite;
    bool MemToReg;
    bool Branch;
    bool Zero;
    uint32_t BranchAddress;
    uint32_t ALUResult;
    uint32_t ReadData2;
    uint8_t Destination;
    bool tempRegWrite;
    bool tempMemRead;
    bool tempMemWrite;
    bool tempMemToReg;
    bool tempBranch;
    bool tempZero;
    uint32_t tempBranchAddress;
    uint32_t tempALUResult;
    uint32_t tempReadData2;
    uint8_t tempDestination;
};

#endif
