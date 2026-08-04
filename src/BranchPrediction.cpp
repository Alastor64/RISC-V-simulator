#include "CPU.hpp"
#include "Tempor.hpp"
CPU::BranchPrediction::BranchPrediction(CPU *_) : Module(_) {}
void CPU::BranchPrediction::update() {}
void CPU::BranchPrediction::run() {
    const word CLR = holder->CLR.getv();
    const word blockROB = holder->blockROB.getv();
    const word blockLSQ = holder->blockLSQ.getv();
    const word blockRS = holder->blockRS.getv();
    const word PC = holder->PC.getv();
    const word CLR_ADDR = holder->CLR_ADDR.getv();
    Tempor ins_PC, ins_PC_next, _PC;
    if (CLR) {
        ins_PC_next = ins_PC = 0;
        _PC = CLR_ADDR;
    } else if (blockLSQ || blockROB || blockRS) {
        ins_PC_next = ins_PC = 0;
        _PC = PC;
    } else {
        ins_PC = PC;
        ins_PC_next = _PC = PC + 4;
    }
    holder->ins_PC_next.write(ins_PC_next());
    holder->ins_PC.write(ins_PC());
    holder->PC.write(_PC());
}