/* -------------------------------------------------------------------------- */
/* IDtoExRegister.h                                                           */
/* Lachlan and Marie                                                          */
/* Represents the ID/EX Stage Register in DataPath                            */
/* -------------------------------------------------------------------------- */

#ifndef IDtoExREGISTER_H
#define IDtoExREGISTER_H

#include "StageRegister.h"
#ifndef MEMORYSTORE_H
#define MEMORYSTORE_H
#include "MemoryStore.h"
#endif

class IDtoExRegister : public StageRegister {
public:
    IDtoExRegister();
    /* set to 1 if the Register is being written to rt and set to 0 if it is being
        written to rd */
    void SetRegDst(bool RegDestVal);

    /* The Textbook's ALUops were not extensive enough to account for
        all of the instructions in the MIPS implementation. Thus, I have
        added a 3rd op line which follow the following:
                            op1     op2     op3
        Insrt. R-type       1       0       0
        LW + SW (add)       0       0       0
        BE (subtract)       0       1       0
        (or)                0       1       1
        (and)               0       0       1
        (SLT)               1       0       1
        LUI                 1       1       1
    */
    // ALUop1, ALUop2, and ALUop3 are all set up in accordance to these values
    void SetALUop1(bool ALUTop1Val);
    void SetALUop2(bool ALUTop2Val);
    void SetALUop3(bool ALUTop3Val);

    /* set to 1 if the ALUsrc comes from an immediate, and set to  0 if the ALU
        src comes from the register */
    void SetALUSrc(bool ALUSrcVal);

    /* Set branch is set to 1 if it is a branch instruction */
    void SetBranch(bool BranchVal);

    /* MemRead is set to 1 if the instruction reads from memory, otherwise 0 */
    void SetMemRead(bool MemReadVal);

    /* MemWrite is set to 1 if the instruction writes to memory, otherwise 0 */
    void SetMemWrite(bool MemWriteVal);

    /* sets the control line to 1 if the instruction will write to a register,
     otherwise set to 0 */
    void SetRegWrite(bool RegWriteVal);

    /* MemToReg is set to 1 if you are writing a value from memory to a register,
        otherwise it is set to 0 */
    void SetMemToReg(bool MemToRegVal);

    /* set to 1 if overflow detection is required, or the operation is signed,
        such as SLT */
    void SetOverflow(bool OverflowVal);

    /* sets the values to the values of PC */
    void SetPC(uint32_t PCVal);

    /* sets readData1 result from the register fetcher */
    void SetReadData1(uint32_t ReadData1Val);

    /* sets readData2 result from the register fetcher */
    void SetReadData2(uint32_t ReadData2Val);

    /* sets the signed immediate value which is found from the Instruction address */
    void SetImmediateValue(uint32_t ImmediateValueVal);

    /* sets the location of the write back destination, either rd or rt */
    void SetDestination(uint8_t DestVal);

    /* sets the number register of the rs register of the instruction */
    void SetRS(uint8_t RSVal);

    /* Sets the instruction to be pulled by the dumpPipeline so we know which Instruction
        is in which stage */
    void SetInstructionForDump(uint32_t InstructionVal);

    /* Sets the MemSize depending on the enum MemEntry size to be read or written
        to memory in the memory stage */
    void SetMemSize(enum MemEntrySize size);

    /* similar to above except the getter functions for the variable */
    bool GetRegDst() const;
    bool GetALUop1() const;
    bool GetALUop2() const;
    bool GetALUop3() const;
    bool GetALUSrc() const;
    bool GetBranch() const;
    bool GetMemRead() const;
    bool GetMemWrite() const;
    bool GetRegWrite() const;
    bool GetMemToReg() const;
    bool GetOverflow() const;
    uint32_t GetPC() const;
    uint32_t GetReadData1() const;
    uint32_t GetReadData2() const;
    uint32_t GetImmediateValue() const;
    uint8_t GetDestination() const;
    uint8_t GetRS() const;
    uint32_t GetInstructionForDump() const;
    enum MemEntrySize GetMemSize() const;

    /* updates the previous version of the register with the new values of the register */
    void CommitValues();

private:
    bool RegDst;
    bool ALUop1;
    bool ALUop2;
    bool ALUop3;
    bool ALUSrc;
    bool Branch;
    bool MemRead;
    bool MemWrite;
    bool RegWrite;
    bool MemToReg;
    bool Overflow;
    uint32_t PC;
    uint32_t ReadData1;
    uint32_t ReadData2;
    uint32_t ImmediateValue;
    uint8_t Dest;
    uint8_t RS;
    uint32_t Instruction;
    enum MemEntrySize memSize;

    bool tempRegDst;
    bool tempALUop1;
    bool tempALUop2;
    bool tempALUop3;
    bool tempALUSrc;
    bool tempBranch;
    bool tempMemRead;
    bool tempMemWrite;
    bool tempRegWrite;
    bool tempMemToReg;
    bool tempOverflow;
    uint32_t tempPC;
    uint32_t tempReadData1;
    uint32_t tempReadData2;
    uint32_t tempImmediateValue;
    uint8_t tempDest;
    uint8_t tempRS;
    uint32_t tempInstruction;
    enum MemEntrySize tempMemSize;
};

#endif
