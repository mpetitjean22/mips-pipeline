void runExecute(){
// (1) Read from ID/EX
    bool ALUop1     = IDtoEX.GetALUop1();
    bool ALUop2     = IDtoEX.GetALUop2();
    bool regDst     = IDtoEX.GetRegDst();
    bool ALUSrc     = IDtoEX.GetALUSrc();
    uint32_t readData1  = IDtoEX.GetReadData1();
    uint32_t readData2  = IDtoEX.GetReadData2();
    uint32_t PC     = IDtoEX.GetPC();
    uint8_t shmt    = IDtoEX.GetImmediateValue(); // shorten this (6 - 10)
    uint8_t funct   = IDtoEX.GetImmediateValue(); // shorten This (5 - 0)
    uint8_t rs      = IDtoEX.GetRS();
    uint8_t dest1   = IDtoEX.GetDest1();
    uint8_t dest2   = IDtoEX.GetDest2();

    uint32_t ALUResult;

// (2) ALU Execution
    if(ALUop1 == 1){
        if(funct == 32){
        // simple add instruction --> ALUSelector = 2
        // source #1 = readData1 and source #2 = readData2
            ALUResult = ReadData1 + ReadData2;
        }
    }

// (3) Write to EX/MEM register
    EXtoMEM.SetRegWrite(IDtoEX.GetRegWrite());
    EXtoMEM.SetMemRead(IDtoEX.GetMemRead());
    EXtoMEM.SetMemWrite(IDtoEX.GetMemWrite());
    EXtoMEM.SetMemToReg(IDtoEX.GetMemToReg());
    EXtoMEM.SetBranch(IDtoEX.GetBranch());
    EXtoMEM.SetZero(IDtoEX.GetZero());
    EXtoMEM.SetALUResult(ALUResult);
    EXtoMEM.SetBranchAddress(PC + IDtoEX.getImmediate() << 2);
    EXtoMEM.ReadData1(readData2);
    EXtoMEM.SetDestination(dest2); // hard coded for now
}
