#include <cstdint>
/* stores all the values of the MEM/EX register */

/* ------------------------------------------------------------------ */
/* setter functions */

void setRegWrite(bool RegWriteVal);
void setMemToReg(bool MemToRegVal);
void setMemoryOutput(uint32_t MemoryOutputVal);
void setALUResult(uint32_t ALUResultVal);
void setDestination(uint8_t DesintationVal);

/* ------------------------------------------------------------------ */
/* getter functions */

bool getRegWrite(void);
bool getMemToReg(void);
uint32_t getMemoryOutput(void);
uint32_t getALUResult(void);
uint8_t getDestination(void);

/* ------------------------------------------------------------------ */
/* commits the old version of the register to the new version */

 void commitValues(void);

 /* ------------------------------------------------------------------ */
