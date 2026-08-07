#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
#include "RS.hpp"
void RS::readCDB() {
    cw ct[] = {holder->CDB_LSQ_tag.getv(), holder->CDB_RS_tag.getv()};
    cw cv[] = {holder->CDB_LSQ_val.getv(), holder->CDB_RS_val.getv()};

    for (word i = 0; i < RS_SIZE; i++) {
        if (op[i].getv() != 0) {
            for (word t = 0; t < 2; t++) {
                if (q1[i].getv() != 0 && q1[i].getv() == ct[t]) {
                    q1[i].write(0);
                    v1[i].write(cv[t]);
                }
                if (q2[i].getv() != 0 && q2[i].getv() == ct[t]) {
                    q2[i].write(0);
                    v2[i].write(cv[t]);
                }
            }
        }
    }
}