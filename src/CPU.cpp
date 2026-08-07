#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
#include <cstdio>
#ifdef DEBUG
void CPU::print() {
    printf("PC=%d:\n", PC.getv());
    for (int i = 0; i < MAX_REG_NUM; i++) {
        printf("reg[%d]:val=%d  tag=%d\n", i, reg[i].getv(), rat.tag[i].getv());
    }
}
#endif
CPU::CPU()
    : regWrite(reg, MAX_REG_NUM, 2), regRead(reg, MAX_REG_NUM), fetch(this),
      reseter(this), BP(this), decode(this), issue(this), rat(this), rob(this),
      rs(this), lsq(this) {};
Module::Module(CPU *_holder) : holder(_holder) {}
void CPU::update() {
    // port and tempor update must be former than reg
    fetch.update();
    decode.update();
    reseter.update();
    BP.update();
    rat.update();
    rob.update();
    issue.update();
    rs.update();
    lsq.update();

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
    CM_tag.update();
    CDB_LSQ_tag.update();
    CDB_RS_tag.update();
    CDB_LSQ_val.update();
    CDB_RS_val.update();
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
    lsq.init();
}
void CPU::run() {
    long long tick = 0;
    long long maxtick = 1e15;
    mem.loadInstruction();
    init();
    while (tick < maxtick) {
        tick++;

        fetch.run();
        BP.run();
        reseter.run();
        decode.run();
        rat.run();
        rob.run();
        issue.run();
        rs.run();
        lsq.run();

        update();

#ifdef DEBUG
        printf("tick:%lld\n", tick);
        // print();
#endif

        if (terminate.getv() == TERMINATE)
            break;
    }
    if (tick >= maxtick) {
        std::printf("too many ticks,shut down now\n");
    } else {
        std::printf("%d\n", (reg[10].getv() & getLF1(8)));
    }
}