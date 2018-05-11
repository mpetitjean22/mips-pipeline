static bool isJumpInstruction;
static uint32_t Instruction;

static uint8_t getOpcode(uint32_t instr){
    return (uint8_t)((instr >> 26) & 0x3f);
}
static uint8_t getReadRegister1(uint32_t instr){
    return (uint8_t)((instr >> 21) & 1F);
}
static uint8_t getReadRegister1(uint32_t instr){
    return (uint8_t)((instr >> 16) & 1F);
}
static uint8_t getDest2(uint32_t instr){
    return (uint8_t)((instr >> 11) & 1F);
}
static uint16_t getImmediate(uint32_t instr){
    return instr & 0xffff;
}
static uint32_t somethingToSignExtend(uint16_t imm){
    uint32_t newMasked;
    if (((1 << 15) & imm) >> 15) {
        newMasked = (uint32_t)(0xFFFF0000 | imm);
    } else {
        newMasked = (uint32_t)(0x00000000 | imm);
    }
    return newMasked;
}
uint16_t getfunct(uint32_t instr){
    return instr & 0x3f;
}

void run(){
    uint8_t opcode;
    uint8_t readRegister1;
    uint8_t readRegister2;
    uint8_t dest2;
    uint16_t immediate;
    uint8_t funct;

    isJumpInstruction = false;

    // lets just say IFtoIDRegister IFtoID was initialized somewhere
    // seperate it up
    Instruction = IFtoID.GetInstruction;
    opcode = getOpcode(Instruction);                    // 26 - 31
    readRegister1 = getReadRegister1(Instruction);      // 21 - 25
    readRegister2 = getReadRegister2(Instruction);      // 16 - 20
    dest2 = getDest2(Instruction);                      // 11 - 15
    immediate = somethingToSignExtend(
                    getImmediate(Instruction));         // 0 - 15
    funct = getfunct(Instruction);                      // 0 - 5

    // do we need to stall?
    if(IDtoEX.GetMemRead == 1 &&
        (IDtoEx.GetDest1 == readRegister1) ||
        (IDtoEX.GetDest1 == readRegister2)){
            // memwrite, memread, branch, regwrite --> 0
            IDtoEX.SetMemWrite = 0;
            IDtoEX.SetMemRead = 0;
            IDtoEX.SetBranch = 0;
            IDtoEX.SetRegWrite = 0;

            // need to figure out how to communicate to IF to stall
        }
    // no we dont stall (yay)
    else{
        // write the new registers up
        IDtoEX.SetPC = IFtoID.GetPC;
        // IDtoEX.SetReadData1 = CALL TO REGISTER (readregister1)
        // IDtoEX.SetReadData2 = CALL TO REGISTER (readregister2)
        IDtoEx.SetImmediateValue = immediate;
        IDtoEx.SetDest1 = readRegister2;
        IDtoEX.SetDest2 = dest2;

        // this is where we would have to hard code control flags
        writeControlFlags(opcode,func)
    }
}

void writeControlFlags(uint8_t opcode, uint8_t funct){
        /* hard code them here later */
}

void readFromRegister(){
    /* function that reads from the registers when called upon by
        write back since it takes the first half of the cycle */
        
}
/*
    (1) Get the instruction from IF/ID
    (2) Send the PC from ID/EX straight to ID/EX
    (3) Figure out what the instruction is and have a way to know
        what all of the control things should be (would have to be
        hard coded for each of the instructions)
            - RegDest
            - ALUop1 + ALUop2
            - Branch
            - MemRead
            - MemWrite
            - RegWrite
            - MemToReg
    (4) Acces the two registers that you need to read from
            - ReadData1 is the result
            - Read Data2 is the second result
    (5) If there is an immediate, then set it
    (6) If RegWrite (from MEM/WB) == 1
        - Use the Destination (MEM/WB)
        - Use the calculated value from (MEM/WB) from the first half
            of the cycle to determine what you are writing in
*/
