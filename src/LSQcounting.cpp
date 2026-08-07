#include "CPU.hpp"
#include "LSQ.hpp"
#include "MyConstAndTypedef.hpp"
void LSQ::counting() {
    for (word i = 0; i < LSQ_SIZE; i++) {
        if (op[i].getv() == 0)
            continue;
        if (count[i].getv() == 0)
            continue;
        if (count[i].getv() == memtick) {
            if (op[i].getv() == OP_LSQ_store) {
                holder->mem.write_byte(val[i].getv(), addr[i].getv());
                pop(i);
            } else {
                if (!CDBflag()) {
                    CDBflag = 1;
                    holder->CDB_LSQ_tag.write(target[i].getv());
                    holder->CDB_LSQ_val.write(val[i].getv());
                    pop(i);
                }
            }
        } else {
            count[i].write(count[i].getv() + 1);
            if (op[i].getv() == OP_LSQ_load && count[i].getv() == memtick - 1) {
                val[i].write(holder->mem.get_byte(addr[i].getv()));
            }
        }
    }
}