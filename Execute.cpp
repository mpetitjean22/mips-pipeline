#include "Execute.h"
#include "sim.h"

#define OP_JAL = 0x3

extern IDtoExRegister* IDtoEX;
extern IFtoIDRegister* IFtoID;
extern EXtoMemRegister* EXtoMEM;
extern MemToWBRegister* MEMtoWB;
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
enum CONTROL_VALS
{
    AND         = 0,
    OR          = 1,
    ADD         = 2,
    SUBTRACT    = 6,
    SLT         = 7,
    SHIFT_LEFT  = 8,
    SHIFT_RIGHT = 9,
    NOR         = 12,
    SHIFT_16    = 13
};
// from golden sim
static uint8_t getSign(uint32_t value)
{
    return (value >> 31) & 0x1;
}
static int performALU(uint32_t source1, uint32_t source2, uint8_t Control, uint8_t shmt, bool overflow){
    uint32_t Result = 0;
    bool Zero = 0;
    bool overflowfound = false;
    switch(Control){
        case AND:
            Result = (uint32_t)(source1 - source2);
            break;
        case OR:
            Result = (uint32_t)(source1 | source2);
            break;
        case ADD:
            Result = (uint32_t)((int32_t)source1 + (int32_t)source2);
            if(overflow){
                overflowfound = getSign(source1) == getSign(source2) && getSign(source2) != getSign(Result);
            }
            break;
        case SUBTRACT:
            Result = (uint32_t)((int32_t)source1 - (int32_t)source2);
            if(overflow){
                overflowfound = getSign(source1) != getSign(source2) && getSign(source2) == getSign(Result);
            }
            break;
        case SLT:
            // I'm just handling this overflow as if it were signed
            if(overflow){
                if((int32_t)source1 < (int32_t)source2){
                    Result = (uint32_t)1;
                }
            }
            else{
                if(source1 < source2){
                    Result = (uint32_t)1;
                }
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
        case SHIFT_16:
            Result = (uint32_t)source2 << 16;
            break;
    }
    if(Result == 0){
        Zero = 1;
    }
    if(overflowfound){
        return 1;
    }
    EXtoMEM->SetALUResult(Result);
    EXtoMEM->SetZero(Zero);
    return 0;
}
static uint8_t ALUControl(uint8_t func, bool op1, bool op2, bool op3){
    // R type instruction
    uint8_t ALUControlInput = 0;
    if(op1==1 && op2 == 0 && op3 == 0){
        switch(func){
            case FUN_ADD:
            case FUN_ADDU:
                ALUControlInput = ADD;
                break;
            case FUN_AND:
                ALUControlInput = AND;
                break;
            case FUN_JR:                        // IMPLEMENT JUMPS!
                break;
            case FUN_NOR:
                ALUControlInput = NOR;
                break;
            case FUN_OR:
                ALUControlInput = OR;
                break;
            case FUN_SLT:
            case FUN_SLTU:
                ALUControlInput = SLT;
                break;
            case FUN_SLL:
                ALUControlInput = SHIFT_LEFT;
                break;
            case FUN_SRL:
                ALUControlInput = SHIFT_RIGHT;
                break;
            case FUN_SUB:
            case FUN_SUBU:
                ALUControlInput = SUBTRACT;
                break;
        }
    }
    else if(op1 == 0 && op2 ==0 && op3==0){
        ALUControlInput = ADD;
    }
    else if(op1 == 0 && op2 == 1 && op3 == 0){
        ALUControlInput = SUBTRACT;
    }
    else if(op1 == 0 && op2 == 1 && op3 == 1){
        ALUControlInput = OR;
    }
    else if(op1 == 0 && op2 == 0 && op3 == 1){
        ALUControlInput = AND;
    }
    else if(op1 == 1 && op2 == 0 && op3 == 1){
        ALUControlInput = SLT;
    }
    else if (op1 == 1 && op2 == 1 && op3 == 1) {
        ALUControlInput = SHIFT_16;
    }
    return ALUControlInput;
}

void runExecute(){
// (1) Read from ID/EX
    bool ALUop1     = IDtoEX->GetALUop1();
    bool ALUop2     = IDtoEX->GetALUop2();
    bool ALUop3     = IDtoEX->GetALUop3();
    bool regDst     = IDtoEX->GetRegDst();
    bool ALUSrc     = IDtoEX->GetALUSrc();
    bool Overflow   = IDtoEX->GetOverflow();
    uint32_t readData1  = IDtoEX->GetReadData1();
    uint32_t readData2  = IDtoEX->GetReadData2();
    uint32_t immediate  = IDtoEX->GetImmediateValue();
    uint32_t PC     = IDtoEX->GetPC();
    uint8_t shmt    = ((IDtoEX->GetImmediateValue()) << 6) & 0x1F;
    uint8_t funct   = (IDtoEX->GetImmediateValue()) & 0x3F;
    uint8_t rs      = IDtoEX->GetRS();
    uint8_t dest   = IDtoEX->GetDestination();

//(1.5) Check for the need for a EX to EX forward
// check for readdata1
    if (EXtoMEM->GetRegWrite() &&
        rs != 0 &&
        EXtoMEM->GetDestination() == rs){
        readData1 = EXtoMEM->GetALUResult();
    } else if (MEMtoWB->GetRegWrite() &&
               rs != 0 &&
               MEMtoWB->GetDestination() == rs){
        if (MEMtoWB->GetMemToReg()) {
            readData1 = MEMtoWB->GetMemoryOutput();
        } else {
            readData1 = MEMtoWB->GetALUResult();
        }
    }

// check for readdata2
    if(EXtoMEM->GetRegWrite() &&
        dest != 0 &&
        EXtoMEM->GetDestination() == dest){
        readData2 = EXtoMEM->GetALUResult();
    } else if (MEMtoWB->GetRegWrite() &&
               dest != 0 &&
               MEMtoWB->GetDestination() == dest){
        if (MEMtoWB->GetMemToReg() == 1) {
            readData2 = MEMtoWB->GetMemoryOutput();
        } else {
            readData2 = MEMtoWB->GetALUResult();
        }
    }

// (2) ALU Execution
    bool exceptionJump;
    if(ALUSrc){
        exceptionJump = performALU(readData1, immediate, ALUControl(funct, ALUop1, ALUop2, ALUop3), shmt, Overflow);
    }
    else{
        exceptionJump = performALU(readData1, readData2, ALUControl(funct, ALUop1, ALUop2, ALUop3), shmt, Overflow);
    }
    if(exceptionJump){
        EXtoMEM->SetRegWrite(false);
        EXtoMEM->SetMemRead(false);
        EXtoMEM->SetMemWrite(false);
        EXtoMEM->SetBranch(false);
        EXtoMEM->SetZero(false);
        EXtoMEM->SetALUResult(0);
        EXtoMEM->SetReadData2(0);
        EXtoMEM->SetDestination(0);
        EXtoMEM->SetInstructionForDump(0);

        IDtoEX->SetRegDst(false);
        IDtoEX->SetALUop1(false);
        IDtoEX->SetALUop2(false);
        IDtoEX->SetALUop3(false);
        IDtoEX->SetALUSrc(false);
        IDtoEX->SetBranch(false);
        IDtoEX->SetMemRead(false);
        IDtoEX->SetMemWrite(false);
        IDtoEX->SetRegWrite(false);
        IDtoEX->SetMemToReg(false);
        IDtoEX->SetOverflow(false);
        IDtoEX->SetPC(0);
        IDtoEX->SetReadData1(0);
        IDtoEX->SetReadData2(0);
        IDtoEX->SetImmediateValue(0);
        IDtoEX->SetDestination(0);
        IDtoEX->SetRS(0);
        IDtoEX->SetInstructionForDump(0);

        IFtoID->SetPC(0);
        IFtoID->SetInstruction(0);

        IF_pleaseBranch((int32_t)0x8000);
        IF_setPCWrite(true);
        IF_unsetHalted();
        exceptionJump = false;
    }
// (3) Write to EX/MEM register
    EXtoMEM->SetDestination(IDtoEX->GetDestination());
    EXtoMEM->SetRegWrite(IDtoEX->GetRegWrite());
    EXtoMEM->SetMemRead(IDtoEX->GetMemRead());
    EXtoMEM->SetMemWrite(IDtoEX->GetMemWrite());
    EXtoMEM->SetMemToReg(IDtoEX->GetMemToReg());
    EXtoMEM->SetBranch(IDtoEX->GetBranch());
    EXtoMEM->SetReadData2(readData2);
    EXtoMEM->SetInstructionForDump(IDtoEX->GetInstructionForDump());
    EXtoMEM->SetMemSize(IDtoEX->GetMemSize());
    setInstruction(2, IDtoEX->GetInstructionForDump());
}
