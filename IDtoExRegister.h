#ifndef IDtoExREGISTER_H
#define IDtoExREGISTER_H

#include "Register.h"

class IDtoExRegister : public Register {
public:
    IDtoExRegister();
    void SetRegDst(bool RegDestVal);
    void SetALUop1(bool ALUTop1Val);
    void SetALUop2(bool ALUTop2Val);
    void SetALUSrc(bool ALUSrcVal);
    void SetBranch(bool BranchVal);
    void SetMemRead(bool MemReadVal);
    void SetMemWrite(bool MemWriteVal);
    void SetRegWrite(bool RegWriteVal);
    void SetMemToReg(bool MemToRegVal);

    void SetPC(uint32_t PCVal);
    void SetReadData1(uint32_t ReadData1Val);
    void SetReadData2(uint32_t ReadData2Val);
    void SetImmediateValue(uint32_t ImmediateValueVal);
    void SetDest1(uint8_t Dest1Val);
    void SetDest2(uint8_t Dest2Val);
    void SetRS(uint8_t RSVal);

    bool GetRegDst() const;
    bool GetALUop1() const;
    bool GetALUop2() const;
    bool GetALUSrc() const;
    bool GetBranch() const;
    bool GetMemRead() const;
    bool GetMemWrite() const;
    bool GetRegWrite() const;
    bool GetMemToReg() const;
    uint32_t GetPC() const;
    uint32_t GetReadData1() const;
    uint32_t GetReadData2() const;
    uint32_t GetImmediateValue() const;
    uint8_t GetDest1() const;
    uint8_t GetDest2() const;
    uint8_t GetRS() const;

    void CommitValues();

private:
    bool RegDst;
    bool ALUop1;
    bool ALUop2;
    bool ALUSrc;
    bool Branch;
    bool MemRead;
    bool MemWrite;
    bool RegWrite;
    bool MemToReg;
    uint32_t PC;
    uint32_t ReadData1;
    uint32_t ReadData2;
    uint32_t ImmediateValue;
    uint8_t Dest1;
    uint8_t Dest2;
    uint8_t RS;

    bool tempRegDst;
    bool tempALUop1;
    bool tempALUop2;
    bool tempALUSrc;
    bool tempBranch;
    bool tempMemRead;
    bool tempMemWrite;
    bool tempRegWrite;
    bool tempMemToReg;
    uint32_t tempPC;
    uint32_t tempReadData1;
    uint32_t tempReadData2;
    uint32_t tempImmediateValue;
    uint8_t tempDest1;
    uint8_t tempDest2;
    uint8_t tempRS;
};

#endif
