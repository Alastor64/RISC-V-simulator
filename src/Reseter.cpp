#include "CPU.hpp"
Reseter::Reseter(CPU *_) : Module(_) {}
void Reseter::update() {}
void Reseter::run() {
    if (holder->CLR.getv()) {
        holder->CLR.write(0);
        holder->CLR_ADDR.write(0);
    }
    holder->regWrite.write(0, 0);
}