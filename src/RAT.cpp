#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
CPU::RAT::RAT(CPU *_)
    : Module(_), RATOr(tag, MAX_REG_NUM), RATRead(tag, MAX_REG_NUM) {}
void CPU::RAT::run() {
    cw CLR = holder->CLR.getv();
    if (CLR == CLEAR_FLAG) {
        for (int i = 0; i < MAX_REG_NUM; i++) {
            tag[i].write(0);
        }
    }
}
void CPU::RAT::update() {
    RATOr.update();
    for (int i = 0; i < MAX_REG_NUM; i++) {
        tag[i].update();
    }
}