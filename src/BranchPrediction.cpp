#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
#include "Tempor.hpp"
CPU::BranchPrediction::BranchPrediction(CPU *_) : Module(_) {}
void CPU::BranchPrediction::update() {
    ins_PC.update();
    ins_PC_next.update();
    _PC.update();
}
void CPU::BranchPrediction::run() {
    cw CLR = holder->CLR.getv();
    cw blockROB = holder->blockROB.getv();
    cw blockLSQ = holder->blockLSQ.getv();
    cw blockRS = holder->blockRS.getv();
    cw PC = holder->PC.getv();
    cw CLR_ADDR = holder->CLR_ADDR.getv();
    if (CLR == CLEAR_FLAG) {
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