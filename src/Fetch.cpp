#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
#include "Tempor.hpp"
CPU::Fetch::Fetch(CPU *_) : Module(_) {}
void CPU::Fetch::update() { ins.update(); }
void CPU::Fetch::run() {
    const word CLR = holder->CLR.getv();
    const word blockROB = holder->blockROB.getv();
    const word blockLSQ = holder->blockLSQ.getv();
    const word blockRS = holder->blockRS.getv();
    const word PC = holder->PC.getv();
    if (CLR == CLEAR_FLAG || blockLSQ || blockROB || blockRS) {
        ins = 0;
    } else {
        ins = holder->mem.get_word(PC);
    }
    holder->ins.write(ins());
}
