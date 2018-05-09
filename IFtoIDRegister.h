#include <cstdint>

void setPC(uint32_t PCVal);
uint32_t getPC(void);

void setInstruction(uint32_t InstructionVal);
uint32_t getInstruction(void);

void commitValues(void);
