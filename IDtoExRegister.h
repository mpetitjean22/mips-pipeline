#include <cstdint>
/* stores the values of the ID/EX register */

/* ------------------------------------------------------------------ */
/* setter functions */

void setRegDst(bool RegDestVal);
void setALUop1(bool ALUTop1Val);
void setALUop2(bool ALUTop2Val);
void setALUSrc(bool ALUSrcVal);
void setBranch(bool BranchVal);
void setMemRead(bool MemReadVal);
void setMemWrite(bool MemWriteVal);
void setRegWrite(bool RegWriteVal);
void setMemToReg(bool MemToRegVal);
void setPC(uint32_t PCVal);
void setReadData1(uint32_t ReadData1Val);
void setReadData2(uint32_t ReadData2Val);
void setImmediateValue(uint32_t ImmediateValueVal);
void setDest1(uint8_t Dest1Val);
void setDest2(uint8_t Dest2Val);
/* ------------------------------------------------------------------ */

/* getter functions */
bool getRegDst(void);
bool getALUop1(void);
bool getALUop2(void);
bool getALUSrc(void);
bool getBranch(void);
bool getMemRead(void);
bool getMemWrite(void);
bool getRegWrite(void);
bool getMemToReg(void);
uint32_t getPC(void);
uint32_t getReadData1(void);
uint32_t getReadData2(void);
uint32_t getImmediateValue(void);
uint8_t getDest1(void);
uint8_t getDest2(void);

/* ------------------------------------------------------------------ */

void commitValues(void);

/* ------------------------------------------------------------------ */
