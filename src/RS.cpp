#include "RS.hpp"
#include "CPU.hpp"
#include "MyClass.hpp"
#include "MyConstAndTypedef.hpp"
RS::RS(CPU *_)
    : Module(_), opRead(op, RS_SIZE), opWrite(op, RS_SIZE, MAX_RS_WRITE_COUNT),
      tagWrite(op, RS_SIZE, MAX_RS_WRITE_COUNT),
      v1Write(op, RS_SIZE, MAX_RS_WRITE_COUNT),
      v2Write(op, RS_SIZE, MAX_RS_WRITE_COUNT),
      q1Write(op, RS_SIZE, MAX_RS_WRITE_COUNT),
      q2Write(op, RS_SIZE, MAX_RS_WRITE_COUNT),
      immWrite(op, RS_SIZE, MAX_RS_WRITE_COUNT) {}
void RS::update() {
    CDBflag.update();
    for (word i = 0; i < RS_SIZE; i++) {
        preEmpty[i].update();
    }
    result.update();
    emptySize.update();
    opRead.update();
    opWrite.update();
    tagWrite.update();
    v1Write.update();
    v2Write.update();
    q1Write.update();
    q2Write.update();
    immWrite.update();
    for (word i = 0; i < RS_SIZE; i++) {
        op[i].update();
        tag[i].update();
        v1[i].update();
        v2[i].update();
        q1[i].update();
        q2[i].update();
        imm[i].update();
    }
}
void RS::push(cw &index, cw &_op, cw &_tag, cw &_v1, cw &_v2, cw &_q1, cw &_q2,
              cw &_imm) {
    opWrite.write(index, _op);
    tagWrite.write(index, _tag);
    v1Write.write(index, _v1);
    v2Write.write(index, _v2);
    q1Write.write(index, _q1);
    q2Write.write(index, _q2);
    immWrite.write(index, _imm);
}
void RS::run() {
    cw CLR = holder->CLR.getv();
    if (CLR == CLEAR_FLAG) {
        for (int i = 0; i < RS_SIZE; i++) {
            op[i].write(0);
            tag[i].write(0);
            v1[i].write(0);
            v2[i].write(0);
            q1[i].write(0);
            q2[i].write(0);
            imm[i].write(0);
        }
        holder->blockRS.write(0);
    } else {
        readCDB();
        ALU();
        countEmpty();
        holder->blockRS.write(emptySize() <= MAX_RS_PUSH * BLOCK_TURN);
    }
    if (CDBflag() == 0) {
        holder->CDB_RS_tag.write(0);
        holder->CDB_RS_val.write(0);
    }
}