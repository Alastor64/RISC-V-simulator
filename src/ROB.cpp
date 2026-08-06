#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
CPU::ROB::ROB(CPU *_)
    : Module(_), tlAdd(&tl, &gene), tagRead(tag, ROB_SIZE),
      readyRead(ready, ROB_SIZE), opRead(op, ROB_SIZE),
      addrRead(addr, ROB_SIZE), valRead(val, ROB_SIZE),
      opWrite(op, ROB_SIZE, MAX_ROB_WRITE_COUNT),
      valWrite(val, ROB_SIZE, MAX_ROB_WRITE_COUNT),
      addrWrite(addr, ROB_SIZE, MAX_ROB_WRITE_COUNT),
      tagWrite(tag, ROB_SIZE, MAX_ROB_WRITE_COUNT),
      readyWrite(ready, ROB_SIZE, MAX_ROB_WRITE_COUNT) {}
void CPU::ROB::push(cw &index, cw &_op, cw &_addr, cw &_val, cw &_tag) {
    tagWrite.write(index, _tag);
    opWrite.write(index, _op);
    addrWrite.write(index, _addr);
    valWrite.write(index, _val);
    readyWrite.write(index, 0);
}
void CPU::ROB::update() {
    ifPop.update();
    ifMEM.update();
    tlAdd.update();
    tagRead.update();
    valRead.update();
    readyRead.update();
    opWrite.update();
    addrWrite.update();
    valWrite.update();
    tagWrite.update();
    readyWrite.update();
    for (int i = 0; i < ROB_SIZE; i++) {
        op[i].update();
        addr[i].update();
        val[i].update();
        tag[i].update();
        ready[i].update();
    }
    hd.update();
    tl.update();
    gene.update();
}
void CPU::ROB::run() {
    cw CLR = holder->CLR.getv();
    if (CLR == CLEAR_FLAG) {
        hd.write(0);
        tl.write(0);
        gene.write(0);
        for (int i = 0; i < ROB_SIZE; i++) {
            op[i].write(0);
            addr[i].write(0);
            val[i].write(0);
            tag[i].write(0);
            ready[i].write(0);
        }
        holder->blockROB.write(0);
    } else {
        readCDB();
        commit();
        holder->blockROB.write(
            hd.getv() != tl.getv() &&
            ((hd.getv() - tl.getv()) & getLF1(ROB_SIZE_WIDTH)) <=
                MAX_ROB_PUSH * BLOCK_TURN + 1);
    }
    if (ifMEM() == 0)
        holder->CM_tag.write(0);
    if (ifPop()) {
        cw HD = hd.getv();
        opWrite.write(HD, 0);
        addrWrite.write(HD, 0);
        valWrite.write(HD, 0);
        tagWrite.write(HD, 0);
        readyWrite.write(HD, 0);
        hd.write((HD + 1) & getLF1(ROB_SIZE_WIDTH));
    }
}