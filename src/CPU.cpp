#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
#include <cstdio>
CPU::CPU()
    : regWrite(reg, MAX_REG_NUM, 1), regRead(reg, MAX_REG_NUM), fetch(this),
      reseter(this), BP(this), decode(this), issue(this), rat(this),
      rob(this) {};
CPU::Module::Module(CPU *_holder) : holder(_holder) {}

void CPU::update() {
    // port and tempor update must be former than reg
    fetch.update();
    decode.update();
    reseter.update();
    BP.update();
    rat.update();
    regWrite.update();
    regRead.update();
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
    terminate.update();
}
void CPU::init() {
    terminate.write(0);
    CLR.write(1);
    CLR_ADDR.write(0);
    terminate.update();
    CLR.update();
    CLR_ADDR.update();
    for (int i = 0; i < MAX_REG_NUM; i++) {
        reg[i].write(0);
        reg[i].update();
    }
}
void CPU::run() {
    mem.loadInstruction();
    init();
    while (1) {

        fetch.run();
        BP.run();
        reseter.run();
        decode.run();
        rat.run();

        update();
        if (terminate.getv() == TERMINATE)
            break;
    }
    std::printf("%d\n", (reg[10].getv() & getLF1(8)));
}