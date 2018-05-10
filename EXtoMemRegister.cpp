/* ExToMem */
/*
    (1) RegWrite
    (2) MemWrite
    (3) MemRead
    (4) MemToReg
    (5) Branch
    (6) Zero (result on ALU?)
    (7) Branch Address --> 32
    (8) ALU result --> 32
    (9) ReadData2 --> 32
    (10) Destination --> 5
*/

/* ------------------------------------------------------------------ */

static bool RegWrite;
static bool MemRead;
static bool MemWrite;
static bool MemToReg;
static bool Branch;
static bool Zero;

static uint32_t BranchAddress;
static uint32_t ALUResult;
static uint32_t ReadData2;

static uint8_t Destination;

/* ------------------------------------------------------------------ */

static bool tempRegWrite;
static bool tempMemRead;
static bool tempMemWrite;
static bool tempMemToReg;
static bool tempBranch;
static bool tempZero;

static uint32_t tempBranchAddress;
static uint32_t tempALUResult;
static uint32_t tempReadData2;

static uint8_t tempDestination;

/* ------------------------------------------------------------------ */

void setRegWrite(bool RegWriteVal){
    tempRegWrite = RegWriteVal;
}
void setMemRead(bool MemReadVal){
    tempMemRead = MemReadVal;
}
void setMemWrite(bool MemWriteVal){
    tempMemWrite = MemWriteVal;
}
void setMemToReg(bool MemToRegVal){
    tempMemToReg = MemToRegVal;
}
void setBranch(bool BranchVal){
    tempBranch = BranchVal;
}
void setZero(bool ZeroVal){
    tempZero = ZeroVal;
}
void setALUResult(uint32_t ALUResultVal){
    tempALUResult = ALUResultVal;
}
void setBranchAddress(uint32_t BranchAddressVal){
    tempBranchAddress = BranchAddressVal;
}
void setReadData2(uint32_t ReadData2Val){
    tempReadData2 = ReadData2Val;
}
void setDestination(uint8_t DesintationVal){
    tempDestination = DesintationVal;
}

/* ------------------------------------------------------------------ */

bool getRegWrite(void){
    return RegWrite;
}
bool getMemRead(void){
    return MemRead;
}
bool getMemWrite(void){
    return MemWrite;
}
bool getMemToReg(void){
    return MemToReg;
}
bool getBranch(void){
    return Branch;
}
bool getZero(void){
    return Zero;
}
uint32_t getALUResult(void){
    return ALUResult;
}
uint32_t getBranchAdress(void){
    return BranchAddress;
}
uint32_t getReadData2(void){
    return ReadData2;
}
uint8_t getDestination(void){
    return Destination;
}

/* ------------------------------------------------------------------ */
