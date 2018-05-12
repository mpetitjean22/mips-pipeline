#include "Execute.h"
#include "sim.h"

extern IDtoExRegister* IDtoEX;
extern EXtoMemRegister* EXtoMEM;
enum FUN_IDS
{
    FUN_ADD = 0x20,
    FUN_ADDU = 0x21,
    FUN_AND = 0x24,
    FUN_JR = 0x08,
    FUN_NOR = 0x27,
    FUN_OR = 0x25,
    FUN_SLT = 0x2a,
    FUN_SLTU = 0x2b,
    FUN_SLL = 0x00,
    FUN_SRL = 0x02,
    FUN_SUB = 0x22,
    FUN_SUBU = 0x23
};

static void performALU(uint32_t source1, uint32_t source2, uint8_t Control){
    uint32_t Result = 0;
    bool Zero = 0;

    switch(Control){
        // add
        case 2:
            Result=(uint32_t)(source1 + source2);
            break;
    }
    if(Result == 0){
        Zero = 1;
    }
    EXtoMEM->SetALUResult(Result);
    EXtoMEM->SetZero(Zero);
}
static uint8_t ALUControl(uint8_t func, bool op1, bool op2){
    // R type instruction
    uint8_t ALUControlInput = 0;
    if(op1){
        switch(func){
            case FUN_ADD:
            case FUN_ADDU:
                ALUControlInput = 2;
                break;
        }
    }
    return ALUControlInput;
}
void runExecute(){
// (1) Read from ID/EX
    bool ALUop1     = IDtoEX->GetALUop1();
    bool ALUop2     = IDtoEX->GetALUop2();
    bool regDst     = IDtoEX->GetRegDst();
    bool ALUSrc     = IDtoEX->GetALUSrc();
    uint32_t readData1  = IDtoEX->GetReadData1();
    uint32_t readData2  = IDtoEX->GetReadData2();
    uint32_t immediate  = IDtoEX->GetImmediateValue();
    uint32_t PC     = IDtoEX->GetPC();
    uint8_t shmt    = IDtoEX->GetImmediateValue(); // shorten this (6 - 10)
    uint8_t funct   = (IDtoEX->GetImmediateValue()) & 0x3F;
    uint8_t rs      = IDtoEX->GetRS();
    uint8_t dest1   = IDtoEX->GetDest1();
    uint8_t dest2   = IDtoEX->GetDest2();

    uint32_t ALUResult;

// (2) ALU Execution
    if(ALUSrc){
        performALU(readData1, immediate, ALUControl(funct, ALUop1, ALUop2));
    }
    else{
        performALU(readData1, readData2, ALUControl(funct, ALUop1, ALUop2));
    }

// (3) Write to EX/MEM register

    EXtoMEM->SetRegWrite(IDtoEX->GetRegWrite());
    EXtoMEM->SetMemRead(IDtoEX->GetMemRead());
    EXtoMEM->SetMemWrite(IDtoEX->GetMemWrite());
    EXtoMEM->SetMemToReg(IDtoEX->GetMemToReg());
    EXtoMEM->SetBranch(IDtoEX->GetBranch());
    //EXtoMEM->SetBranchAddress(PC + IDtoEX->GetImmediate() << 2);
    EXtoMEM->SetReadData2(readData2);
    EXtoMEM->SetDestination(dest2); // hard coded for now

    setCurrentInstructionNum(3, getCurrentInstructionNum(2));
}
