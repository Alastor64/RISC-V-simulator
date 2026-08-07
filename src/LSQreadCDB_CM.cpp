#include "CPU.hpp"
#include "LSQ.hpp"
#include "MyConstAndTypedef.hpp"
void LSQ::readCDB_CM() {
    cw ct[] = {holder->CDB_LSQ_tag.getv(), holder->CDB_RS_tag.getv()};
    cw cv[] = {holder->CDB_LSQ_val.getv(), holder->CDB_RS_val.getv()};

    for (word i = 0; i < LSQ_SIZE; i++) {
        if (op[i].getv() == 0)
            continue;
        for (word t = 0; t < 2; t++) {
            if (qa[i].getv() && qa[i].getv() == ct[t]) {
                qa[i].write(0);
                addr[i].write(cv[t] + offet[i].getv());
            }
            if (qv[i].getv() && qv[i].getv() == ct[t]) {
                qv[i].write(0);
                val[i].write(cv[t] >> (8 * offet[i].getv()) & getLF1(8));
            }
        }
        if (op[i].getv() == OP_LSQ_store &&
            target[i].getv() == holder->CM_tag.getv()) {
            if (qa[i].getv() || qv[i].getv() || count[i].getv())
                throw "unexpected error in read cdb lsq";
            count[i].write(1);
        }
    }
}