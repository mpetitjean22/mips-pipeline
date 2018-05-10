#include "IDtoExRegister.h"
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

/* ------------------------------------------------------------------ */

static bool RegDst;
static bool ALUop1;
static bool ALUop2;
static bool ALUSrc;
static bool Branch;
static bool MemRead;
static bool MemWrite;
static bool RegWrite;
static bool MemToReg;

static uint32_t PC;
static uint32_t ReadData1;
static uint32_t ReadData2;
static uint32_t ImmediateValue;

/* gonna have to check to make sure its actually 5 bits */
static uint8_t Dest1;
static uint8_t Dest2;

/* ------------------------------------------------------------------ */

static bool tempRegDst;
static bool tempALUop1;
static bool tempALUop2;
static bool tempALUSrc;
static bool tempBranch;
static bool tempMemRead;
static bool tempMemWrite;
static bool tempRegWrite;
static bool tempMemToReg;

static uint32_t tempPC;
static uint32_t tempReadData1;
static uint32_t tempReadData2;
static uint32_t tempImmediateValue;

/* gonna have to check to make sure its actually 5 bits */
static uint8_t tempDest1;
static uint8_t tempDest2;

/* ------------------------------------------------------------------ */

void setRegDst(bool RegDestVal){
    tempRegDst = RegDestVal;
}
void setALUop1(bool ALUTop1Val){
    tempALUop1 = ALUop1Val;
}
void setALUop2(bool ALUTop2Val){
    tempALUop2 = ALUop2Val;
}
void setALUSrc(bool ALUSrcVal){
    tempALUSrc = ALUSrcVal;
}
void setBranch(bool BranchVal){
    tempBranch = BranchVal;
}
void setMemRead(bool MemReadVal){
    tempMemRead = MemReadVal;
}
void setMemWrite(bool MemWriteVal){
    tempMemWrite = MemWriteVal;
}
void setRegWrite(bool RegWriteVal){
    tempRegWrite = RegWriteVal;
}
void setMemToReg(bool MemToRegVal){
    tempMemToReg = MemToRegVal;
}
void setPC(uint32_t PCVal){
    tempPC = PCVal;
}
void setReadData1(uint32_t ReadData1Val){
    tempReadData1 = ReadData1Val;
}
void setReadData2(uint32_t ReadData2Val){
    tempReadData2 = ReadData2Val;
}
void setImmediateValue(uint32_t ImmediateValueVal){
    tempImmediateValue = ImmediateValueVal;
}
void setDest1(uint8_t Dest1Val){
    tempDest1 = Dest1Val;
}
void setDest2(uint8_t Dest2Val){
    tempDest2 = Dest2Val;
}

/* ------------------------------------------------------------------ */

bool getRegDst(void){
    return RegDest;
}
bool getALUop1(void){
    return ALUop1;
}
bool getALUop2(void){
    return ALUop2;
}
bool getALUSrc(void){
    return ALUSrc;
}
bool getBranch(void){
    return Branch;
}
bool getMemRead(void){
    return MemRead;
}
bool getMemWrite(void){
    return MemWrite;
}
bool getRegWrite(void){
    return RegWrite;
}
bool getMemToReg(void){
    return MemToReg;
}
uint32_t getPC(void){
    return PC;
}
uint32_t getReadData1(void){
    return ReadData1;
}
uint32_t getReadData2(void){
    return ReadData2;
}
uint32_t getImmediateValue(void){
    return ImmediateValue;
}
uint8_t getDest1(void){
    return Dest1;
}
uint8_t getDest2(void){
    return Dest2;
}

/* ------------------------------------------------------------------ */

void commitValues(void){
    RegDst = tempRegDst;
    ALUop1 = tempALUop1;
    ALUop2 = tempALUop2;
    ALUSrc = tempALUSrc;
    Branch = tempBranch;
    MemRead = tempMemRead;
    MemWrite = tempMemWrite;
    MemToReg = tempMemToReg;
    PC = tempPC;
    ReadData1 = tempReadData1;
    ReadData2 = tempReadData2;
    ImmediateValue = tempImmediateValue;
    Dest1 = tempDest1;
    Dest2 = tempDest2;
}

/* ------------------------------------------------------------------ */
