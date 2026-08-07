#include "LSQ.hpp"
#include "CPU.hpp"
#include "MyClass.hpp"
#include "MyConstAndTypedef.hpp"
LSQ::LSQ(CPU *_)
    : Module(_), opRead(op, LSQ_SIZE),
      opWrite(op, LSQ_SIZE, MAX_LSQ_WRITE_COUNT),
      addrWrite(addr, LSQ_SIZE, MAX_LSQ_WRITE_COUNT),
      valWrite(val, LSQ_SIZE, MAX_LSQ_WRITE_COUNT),
      qaWrite(qa, LSQ_SIZE, MAX_LSQ_WRITE_COUNT),
      qvWrite(qv, LSQ_SIZE, MAX_LSQ_WRITE_COUNT),
      targetWrite(target, LSQ_SIZE, MAX_LSQ_WRITE_COUNT),
      offsetWrite(offet, LSQ_SIZE, MAX_LSQ_WRITE_COUNT),
      countWrite(count, LSQ_SIZE, MAX_LSQ_WRITE_COUNT) {}
void LSQ::update() {
    emptySize.update();
    for (word i = 0; i < LSQ_SIZE; i++) {
        preEmpty[i].update();
        for (word j = 0; j < LSQ_SIZE + 1; j++) {
            frontROB[i][j].update();
            frontVal[i][j].update();
            ifready[i][j].update();
        }
    }
    CDBflag.update();
    opRead.update();
    opWrite.update();
    addrWrite.update();
    valWrite.update();
    qaWrite.update();
    qvWrite.update();
    targetWrite.update();
    offsetWrite.update();
    countWrite.update();
    for (word i = 0; i < LSQ_SIZE; i++) {
        op[i].update();
        addr[i].update();
        val[i].update();
        qa[i].update();
        qv[i].update();
        target[i].update();
        offet[i].update();
        count[i].update();
    }
}
void LSQ::pop(cw &i) {
    op[i].write(0);
    addr[i].write(0);
    val[i].write(0);
    qa[i].write(0);
    qv[i].write(0);
    target[i].write(0);
    offet[i].write(0);
    count[i].write(0);
}
void LSQ::run() {
    cw CLR = holder->CLR.getv();
    countEmpty();
    if (CLR == CLEAR_FLAG) {
        for (word i = 0; i < LSQ_SIZE; i++) {
            if (op[i].getv() == OP_LSQ_store && count[i].getv() > 0)
                continue;
            pop(i);
        }
        holder->blockLSQ.write(0);
    } else {
        readCDB_CM();
        counting();
        checkstore();
        checkload();
        holder->blockLSQ.write(emptySize() <= MAX_LSQ_PUSH * BLOCK_TURN);
    }
    if (!CDBflag()) {
        holder->CDB_LSQ_tag.write(0);
        holder->CDB_LSQ_val.write(0);
    }
}
void LSQ::init() {
    for (word i = 0; i < LSQ_SIZE; i++) {
        op[i].write(0);
        op[i].update();
        addr[i].write(0);
        addr[i].update();
        val[i].write(0);
        val[i].update();
        qa[i].write(0);
        qa[i].update();
        qv[i].write(0);
        qv[i].update();
        target[i].write(0);
        target[i].update();
        offet[i].write(0);
        offet[i].update();
        count[i].write(0);
        count[i].update();
    }
}
void LSQ::push(cw &index, cw &_op, cw &_val, cw &_qa, cw &_qv, cw &_target,
               cw &_offset) {
    if (index >= LSQ_SIZE) {
        throw "you may not write inexist LSQ!";
    }
    op[index].write(_op);
    val[index].write(_val);
    addr[index].write(0);
    qa[index].write(_qa);
    qv[index].write(_qv);
    target[index].write(_target);
    offet[index].write(_offset);
    count[index].write(0);
}
void LSQ::countEmpty() {
    preEmpty[0] = 0;
    for (word i = 0; i < LSQ_SIZE - 1; i++) {
        preEmpty[i + 1] = preEmpty[i]() + (op[i].getv() == 0);
    }
    emptySize = preEmpty[LSQ_SIZE - 1]() + (op[LSQ_SIZE - 1].getv() == 0);
}