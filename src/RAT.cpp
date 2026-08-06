#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
RAT::RAT(CPU *_)
    : Module(_), RATWrite(tag, MAX_REG_NUM), RATRead(tag, MAX_REG_NUM) {}
void RAT::run() {
    cw CLR = holder->CLR.getv();
    if (CLR == CLEAR_FLAG) {
        for (int i = 0; i < MAX_REG_NUM; i++) {
            tag[i].write(0);
        }
    }
}
void RAT::update() {
    RATWrite.update();
    RATRead.update();
    for (int i = 0; i < MAX_REG_NUM; i++) {
        tag[i].update();
    }
}