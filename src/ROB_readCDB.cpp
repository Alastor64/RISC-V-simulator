#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
void CPU::ROB::readCDB() {
    cw CDB_tag[2] = {holder->CDB_RS_tag.getv(), holder->CDB_LSQ_tag.getv()};
    cw CDB_val[2] = {holder->CDB_RS_val.getv(), holder->CDB_LSQ_val.getv()};
    for (int t = 0; t < 2; t++) {
        if (CDB_tag[t] == 0)
            continue;
        for (int i = 0; i < ROB_SIZE; i++) {
            if (CDB_tag[t] == tag[i].getv()) {
                if (ready[i].getv())
                    throw "twice CDB!";
                val[i].write(CDB_val[t]);
                ready[i].write(1);
            }
        }
    }
}