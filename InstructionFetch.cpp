static uint32_t PCsrc;
static uint32_t Instruction;
static uint32_t PC;
void runInstructionFetch(){
    Instuction = getSomething(PC);
    PC = PC + 4;
    
    IFtoID.SetInstruction(Instruction);
    IFtoID.SetPC(PC);
}
