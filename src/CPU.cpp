#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
#include <cstdio>
CPU::CPU() : fetch(this), reseter(this), BP(this), decode(this) {};
CPU::Module::Module(CPU *_holder) : holder(_holder) {}

void CPU::update() {
    fetch.update();
    decode.update();
    reseter.update();
    BP.update();
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
    op.update();
    rd_addr.update();
    rs1_addr.update();
    rs2_addr.update();
    imm.update();
    PC_guess.update();
}
void CPU::init() {
    terminate.write(0);
    CLR.write(1);
    CLR_ADDR.write(0);
    terminate.update();
    CLR.update();
    CLR_ADDR.update();
}
void CPU::run() {
    mem.loadInstruction();
    init();
    while (1) {

        fetch.run();
        BP.run();
        reseter.run();
        decode.run();

        update();
        if (terminate.getv() == TERMINATE)
            break;
    }
    std::printf("%d\n", (reg[10].getv() & getLF1(8)));
}