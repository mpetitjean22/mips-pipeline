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
enum CONTROl_VALS
{
    AND         = 0,
    OR          = 1,
    ADD         = 2,
    SUBTRACT    = 6,
    SLT         = 7,
    SHIFT_LEFT  = 8,
    SHIFT_RIGHT = 9,
    NOR         = 12
};

static void performALU(uint32_t source1, uint32_t source2, uint8_t Control, uint8_t shmt){
    uint32_t Result = 0;
    bool Zero = 0;
    switch(Control){
        case AND:
            Result = (uint32_t)(source1 - source2);
            break;
        case OR:
            Result = (uint32_t)(source1 | source2);
            break;
        case ADD:
            Result = (uint32_t)(source1 + source2);
            break;
        case SUBTRACT:
            Result = (uint32_t)(source1 - source2);
            break;
        case SLT:
            if(source1 < source2){
                Result = (uint32_t)1;
            }
            break;
        case SHIFT_LEFT:
            Result = (uint32_t)(source1 << shmt);
            break;
        case SHIFT_RIGHT:
            Result = (uint32_t)(source1 >> shmt);
            break;
        case NOR:
            Result = (uint32_t)~(source1 | source2);
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
            case FUN_ADD:                       // HANDLE SIGNS!
            case FUN_ADDU:
                ALUControlInput = ADD;
                break;
            case FUN_AND:
                ALUControlInput = AND;
                break;
            case FUN_JR:                        // IMPLEMENT JUMPS!
                break;
            case FUN_NOR:
                // we need a NOR
                break;
            case FUN_OR:
                ALUControlInput = OR;
                break;
            case FUN_SLT:                       // HANDLE SIGNS!
            case FUN_SLTU:
                ALUControlInput = SLT;
                break;
            case FUN_SLL:
                ALUControlInput = SHIFT_LEFT;
                break;
            case FUN_SRL:
                ALUControlInput = SHIFT_RIGHT;
                break;
            case FUN_SUB:                      // HANDLE SIGNS!
            case FUN_SUBU:
                ALUControlInput = SUBTRACT;
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
    uint8_t shmt    = ((IDtoEX->GetImmediateValue()) << 6) & 0x1F;
    uint8_t funct   = (IDtoEX->GetImmediateValue()) & 0x3F;
    uint8_t rs      = IDtoEX->GetRS();
    uint8_t dest1   = IDtoEX->GetDest1();
    uint8_t dest2   = IDtoEX->GetDest2();

    uint32_t ALUResult;

// (2) ALU Execution
    if(ALUSrc){
        performALU(readData1, immediate, ALUControl(funct, ALUop1, ALUop2), shmt);
    }
    else{
        performALU(readData1, readData2, ALUControl(funct, ALUop1, ALUop2), shmt);
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
