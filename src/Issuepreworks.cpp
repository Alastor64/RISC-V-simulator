#include "CPU.hpp"
#include "Issue.hpp"
#include "MyConstAndTypedef.hpp"
void Issue::makeindexs() {
    cw tl = holder->rob.tl.getv();
    cw gene = holder->rob.gene.getv();
    cw CLR = holder->CLR.getv();
    for (word i = 0; i < MAX_ROB_PUSH; i++) {
        cw index = ((tl + i) & getLF1(ROB_SIZE_WIDTH));
        ROBindex[i] = index;
        ROBtag[i] = make_ROB_tag(index, gene, tl);
    }
    for (int i = 0; i < MAX_RS_PUSH; i++) {
        if (CLR == CLEAR_FLAG) {
            RSindex[i] = 0;
            continue;
        }
        for (int j = 0; j < RS_SIZE; j++) {
            if (holder->rs.opRead.read(j))
                continue;
            if (i == 0 || j > RSindex[i - 1]()) {
                RSindex[i] = j;
                break;
            }
        }
    }
}
void Issue::checkROBtag() {
    cw addr[] = {holder->rd_addr.getv(), holder->rs1_addr.getv(),
                 holder->rs2_addr.getv()};
    for (int i = 0; i < 3; i++) {
        if (addr[i] == 0 || addr[i] >= MAX_REG_NUM) {
            rval[i] = 0;
            rtag[i] = 0;
            continue;
        }
        cw t = holder->rat.RATRead.read(addr[i]);
        if (t == 0) {
            rval[i] = holder->regRead.read(addr[i]);
            rtag[i] = 0;
        } else if (t == holder->CDB_LSQ_tag.getv()) {
            rval[i] = holder->CDB_LSQ_val.getv();
            rtag[i] = 0;
        } else if (t == holder->CDB_RS_tag.getv()) {
            rval[i] = holder->CDB_RS_val.getv();
            rtag[i] = 0;
        } else if (holder->rob.readyRead.read(t & getLF1(ROB_SIZE_WIDTH))) {
            rval[i] = holder->rob.valRead.read(t & getLF1(ROB_SIZE_WIDTH));
            rtag[i] = 0;
        } else {
            rval[i] = 0;
            rtag[i] = t;
        }
    }
}