/* MemToWB */
/*
    (1) MemToReg
    (2) RegWrite
    (3) MemoryOutput --> 32
    (4) Destination --> 5
    (5) ALUResult --> 32
*/

/* ------------------------------------------------------------------ */

static bool MemToReg;
static bool RegWrite;

static uint32_t ALUResult;
static uint32_t MemoryOutput;

static uint8_t Destination;

/* ------------------------------------------------------------------ */

static bool tempMemToReg;
static bool tempRegWrite;

static uint32_t tempALUResult;
static uint32_t tempMemoryOutput;

static uint8_t tempDestination;

/* ------------------------------------------------------------------ */

void setRegWrite(bool RegWriteVal){
    tempRegWrite = RegWriteVal;
}
void setMemToReg(bool MemToRegVal){
    tempMemToReg = MemToRegVal;
}
void setMemoryOutput(uint32_t MemoryOutputVal){
    tempMemoryOutput = MemoryOutputVal;
}
void setALUResult(uint32_t ALUResultVal){
    tempALUResult = ALUResultVal;
}
void setDestination(uint8_t DesintationVal){
    tempDestination = DesintationVal;
}

/* ------------------------------------------------------------------ */

bool getRegWrite(void){
    return RegWrite;
}
bool getMemToReg(void){
    return MemToReg;
}
uint32_t getALUResult(void){
    return ALUResult;
}
uint32_t getALUResult(void){
    return ALUResult;
}
uint8_t getDestination(void){
    return Destination;
}

/* ------------------------------------------------------------------ */
