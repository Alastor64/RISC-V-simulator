#include "CPU.hpp"
#include "LSQ.hpp"
#include "MyConstAndTypedef.hpp"
void LSQ::checkstore() {
    for (word i = 0; i < LSQ_SIZE; i++) {
        cw o = op[i].getv();
        if (o == 0)
            continue;
        if (qa[i].getv() || qv[i].getv())
            continue;
        if (count[i].getv())
            continue;
        if (!CDBflag()) {
            CDBflag = 1;
            holder->CDB_LSQ_tag.write(target[i].getv());
            holder->CDB_LSQ_val.write(1);
        }
    }
}