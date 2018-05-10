#include <cstdint>
/* stores the values of the EX/MEM Register */

/* ------------------------------------------------------------------ */
/* setter functions */

void setRegWrite(bool RegWriteVal);
void setMemRead(bool MemReadVal);
void setMemWrite(bool MemWriteVal);
void setMemToReg(bool MemToRegVal);
void setBranch(bool BranchVal);
void setZero(bool ZeroVal);
void setALUResult(uint32_t ALUResultVal);
void setBranchAddress(uint32_t BranchAddressVal);
void setReadData2(uint32_t ReadData2Val);
void setDestination(uint8_t DesintationVal);

/* ------------------------------------------------------------------ */
/* getter functions */

bool getRegWrite(void);
bool getMemRead(void);
bool getMemWrite(void);
bool getMemToReg(void);
bool getBranch(void);
bool getZero(void);
uint32_t getALUResult(void);
uint32_t getBranchAdress(void);
uint32_t getReadData2(void);
uint8_t getDestination(void);

/* ------------------------------------------------------------------ */

void commitValues(void);

/* ------------------------------------------------------------------ */
