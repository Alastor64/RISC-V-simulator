#include "CPU.hpp"
CPU::Reseter::Reseter(CPU *_) : Module(_) {}
void CPU::Reseter::update() {}
void CPU::Reseter::run() {
    if (holder->CLR.getv()) {
        holder->CLR.write(0);
        holder->CLR_ADDR.write(0);
    }
    holder->reg[0].write(0);
}