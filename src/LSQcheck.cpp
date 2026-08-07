#include "CPU.hpp"
#include "LSQ.hpp"
#include "MyConstAndTypedef.hpp"
#include "Tempor.hpp"
void LSQ::checkstore() {
    for (word i = 0; i < LSQ_SIZE; i++) {
        cw o = op[i].getv();
        if (o != OP_LSQ_store)
            continue;
        if (qa[i].getv() || qv[i].getv())
            continue;
        if (count[i].getv())
            continue;
        if (offet[i].getv() == -1)
            continue;
        if (!CDBflag()) {
            offet->write(-1);
            CDBflag = 1;
            holder->CDB_LSQ_tag.write(target[i].getv());
            holder->CDB_LSQ_val.write(1);
        }
    }
}
void LSQ::checkload() {
    for (word i = 0; i < LSQ_SIZE; i++) {
        cw o = op[i].getv();
        cw t = target[i].getv();
        cw a = addr[i].getv();
        if (o != OP_LSQ_load)
            continue;
        if (count[i].getv())
            continue;
        FlexTempor unknown;
        for (word j = 0; j < LSQ_SIZE; j++) {
            if (op[j].getv() == OP_LSQ_store && qa[j].getv() &&
                ROByounger(target[j].getv(), t)) {
                unknown = 1;
                break;
            }
        }
        if (unknown())
            continue;
        frontROB[i][0] = 0;
        frontVal[i][0] = 0;
        ifready[i][0] = 0;
        for (word j = 0; j < LSQ_SIZE; j++) {
            cw iflegal = (op[j].getv() == OP_LSQ_store && addr[j].getv() == a &&
                          ROByounger(target[j].getv(), t));
            cw better = (frontROB[i][j]() == 0 &&
                         ROByounger(frontROB[i][j](), target[j].getv()));
            if (iflegal && better) {
                frontROB[i][j + 1] = target[j].getv();
                frontVal[i][j + 1] = val[j].getv();
                ifready[i][j + 1] = !bool(qv[j].getv());
            } else {
                frontROB[i][j + 1] = frontROB[i][j];
                frontVal[i][j + 1] = frontVal[i][j];
                ifready[i][j + 1] = ifready[i][j];
            }
        }
        cw fr = frontROB[i][LSQ_SIZE]();
        cw fv = frontVal[i][LSQ_SIZE]();
        cw ir = ifready[i][LSQ_SIZE]();
        if (!fr) {
            count[i].write(1);
        } else {
            if (ir) {
                val[i].write(fv);
                count[i].write(memtick);
            }
        }
    }
}