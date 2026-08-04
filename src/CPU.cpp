#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
#include <cstdio>
CPU::CPU() : fetch(this), BP(this) {};
CPU::Module::Module(CPU *_holder) : holder(_holder) {}
void CPU::run() {
    mem.loadInstruction();
    PC.write(0);
    terminate.write(0);
    terminate.update();
    PC.update();
    while (1) {
        fetch.run();
        BP.run();
        update();
        if (terminate.getv() == TERMINATE)
            break;
    }
    std::printf("%d\n", (reg[10].getv() & getLF1(8)));
}
void CPU::update() {
    for (int i = 0; i < MAX_REG_NUM; i++) {
        reg[i].update();
    }
    PC.update();
    CLR.update();
    CLR_ADDR.update();
    blockLSQ.update();
    blockROB.update();
    blockRS.update();
    ins.update();
    ins_PC.update();
    ins_PC_next.update();
}