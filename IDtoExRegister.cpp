#include <stdio.h>
/* IFtoEx Register */
/*
    (1) ALUop1
    (2) ALUop --> op1 and op2
    (3) ALUSrc
    (4) Branch
    (5) MemRead
    (6) MemWrite
    (7) RegWrite
    (8) MemToReg
    (9) PC --> 32 bit
    (10) ReadData1 --> 32
    (11) ReadData2 --> 32
    (12) ImmediateValue  --> 32
    (13) Dest1 --> 5
    (14) Dest2 --> 5
*/
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

    /* gonna have to check to make sure its actually 5 bits */
    uint8_t Dest1;
    uint8_t Dest2;

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

    /* gonna have to check to make sure its actually 5 bits */
    uint8_t tempDest1;
    uint8_t tempDest2;

    void setRegDst(bool RegDestVal, int real){
        if(real){
            RegDest = RegDestVal;
        }
        else{
            tempRegDst = RegDestVal;
        }
    }

    void setALUop1(bool ALUTop1Val, int real){
        if(real){
            ALUop1 = ALUop1Val;
        }
        else{
            tempALUop1 = ALUop1Val;
        }
    }

    void setALUop2(bool ALUTop2Val, int real){
        if(real){
            ALUop2 = ALUop2Val;
        }
        else{
            tempALUop2 = ALUop2Val;
        }
    }

    void setALUSrc(bool ALUSrcVal, int real){
        if(real){
            ALUSrc = ALUSrcVal;
        }
        else{
            tempALUSrc = ALUSrcVal;
        }
    }

    void setBranch(bool BranchVal, int real){
        if(real){
            Branch = BranchVal;
        }
        else{
            tempBranch = BranchVal;
        }
    }

    void setMemRead(bool MemReadVal, int real){
        if(real){
            MemRead = MemReadVal;
        }
        else{
            tempMemRead = MemReadVal;
        }
    }
