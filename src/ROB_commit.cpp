#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
#include "Tempor.hpp"
void CPU::ROB::commit() {
    cw HD = hd.getv();
    if (HD == tl.getv() || !readyRead.read(HD)) {
        return;
    } else {
        cw o = opRead.read(HD), a = addrRead.read(HD), v = valRead.read(HD),
           t = tagRead.read(HD);
        switch (o) {
        case OP_ROB_TMN:
            holder->terminate.write(TERMINATE);
            break;
        case OP_ROB_ALU:
            ifPop = 1;
            if (a != 0) {
                holder->regWrite.write(a, v);
                if (holder->rat.RATRead.read(a) == t)
                    holder->rat.RATOr.write(a, 0);
            }
            break;
        case OP_ROB_CTL:
            if (a == v) {
                ifPop = 1;
            } else {
                holder->CLR.write(1);
                holder->CLR_ADDR.write(v);
            }
            break;
        case OP_ROB_MEM:
            ifPop = 1;
            ifMEM = 1;
            holder->CM_tag.write(t);
            break;
        case OP_ROB_TMP:
            ifPop = 1;
            break;
        case 0:
            throw "nop in commit!";
        default:
            throw "unexpected error in commit!";
        }
    }
}