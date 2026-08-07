#include "CPU.hpp"
#include "Issue.hpp"
#include "MyConstAndTypedef.hpp"
#include "Tempor.hpp"
void Issue::IssueLSQ() {
    cw op = holder->op.getv();
    cw rd_addr = holder->rd_addr.getv();
    cw rs1_addr = holder->rs1_addr.getv();
    cw tl = holder->rob.tl.getv();
    cw gene = holder->rob.gene.getv();
    cw imm = holder->imm.getv();
    FlexTempor pushNum;
    holder->rs.push(RSindex[0](), OP_ALU_add, ROBtag[0](), rval[1](), imm,
                    rtag[1](), 0, 0);
    cw sv0 = (rval[2]()) & getLF1(8);
    cw sv1 = (rval[2]() >> 8) & getLF1(8);
    cw sv2 = (rval[2]() >> 16) & getLF1(8);
    cw sv3 = (rval[2]() >> 24) & getLF1(8);
    switch (op) {
    case OP_LSQ_lbu:
    case OP_LSQ_lb:
    case OP_LSQ_lh:
    case OP_LSQ_lhu:
    case OP_LSQ_lw:
        switch (op) {
        case OP_LSQ_lbu:
            pushNum = 1 + 1;
            holder->lsq.push(LSQindex[0](), OP_LSQ_load, 0, ROBtag[0](), 0,
                             ROBtag[1](), 0);
            break;
        case OP_LSQ_lb:
            pushNum = 1 + 1 + 1;
            holder->rs.push(RSindex[1](), OP_load_signed_bit, ROBtag[2](), 0, 0,
                            ROBtag[1](), 0, 0);
            holder->lsq.push(LSQindex[0](), OP_LSQ_load, 0, ROBtag[0](), 0,
                             ROBtag[1](), 0);
            break;
        case OP_LSQ_lh:
            pushNum = 1 + 2 + 1;
            holder->rs.push(RSindex[1](), OP_load_link_bit, ROBtag[3](), 0, 0,
                            ROBtag[1](), ROBtag[2](), 0);
            holder->lsq.push(LSQindex[0](), OP_LSQ_load, 0, ROBtag[0](), 0,
                             ROBtag[1](), 0);
            holder->lsq.push(LSQindex[1](), OP_LSQ_load, 0, ROBtag[0](), 0,
                             ROBtag[2](), 1);
            break;
        case OP_LSQ_lhu:
            pushNum = 1 + 2 + 1;
            holder->rs.push(RSindex[1](), OP_load_link_bit_u, ROBtag[3](), 0, 0,
                            ROBtag[1](), ROBtag[2](), 0);
            holder->lsq.push(LSQindex[0](), OP_LSQ_load, 0, ROBtag[0](), 0,
                             ROBtag[1](), 0);
            holder->lsq.push(LSQindex[1](), OP_LSQ_load, 0, ROBtag[0](), 0,
                             ROBtag[2](), 1);

            break;
        case OP_LSQ_lw:
            pushNum = 1 + 4 + 2 + 1;
            holder->rs.push(RSindex[1](), OP_load_link_bit_u, ROBtag[5](), 0, 0,
                            ROBtag[1](), ROBtag[2](), 0);
            holder->rs.push(RSindex[2](), OP_load_link_bit_u, ROBtag[6](), 0, 0,
                            ROBtag[3](), ROBtag[4](), 0);
            holder->rs.push(RSindex[3](), OP_load_link_half, ROBtag[7](), 0, 0,
                            ROBtag[5](), ROBtag[6](), 0);
            holder->lsq.push(LSQindex[0](), OP_LSQ_load, 0, ROBtag[0](), 0,
                             ROBtag[1](), 0);
            holder->lsq.push(LSQindex[1](), OP_LSQ_load, 0, ROBtag[0](), 0,
                             ROBtag[2](), 1);
            holder->lsq.push(LSQindex[2](), OP_LSQ_load, 0, ROBtag[0](), 0,
                             ROBtag[3](), 2);
            holder->lsq.push(LSQindex[3](), OP_LSQ_load, 0, ROBtag[0](), 0,
                             ROBtag[4](), 3);

            break;
        default:
            throw "unexpected error in issue LSQ load";
        }
        for (word i = 0; i < pushNum() - 1; i++) {
            holder->rob.push(ROBindex[i](), OP_ROB_TMP, 0, ROBtag[i]());
        }
        holder->rob.push(ROBindex[pushNum() - 1](), OP_ROB_ALU, rd_addr,
                         ROBtag[pushNum() - 1]());
        holder->rat.RATWrite.write(rd_addr, ROBtag[pushNum() - 1]());
        break;
    case OP_LSQ_sb:
    case OP_LSQ_sh:
    case OP_LSQ_sw:
        switch (op) {
        case OP_LSQ_sb:
            pushNum = 1 + 1;
            holder->lsq.push(LSQindex[0](), OP_LSQ_store, sv0, ROBtag[0](),
                             rtag[2](), ROBtag[1](), 0);
            break;
        case OP_LSQ_sh:
            pushNum = 1 + 2;
            holder->lsq.push(LSQindex[0](), OP_LSQ_store, sv0, ROBtag[0](),
                             rtag[2](), ROBtag[1](), 0);
            holder->lsq.push(LSQindex[1](), OP_LSQ_store, sv1, ROBtag[0](),
                             rtag[2](), ROBtag[2](), 1);
            break;
        case OP_LSQ_sw:
            pushNum = 1 + 4;
            holder->lsq.push(LSQindex[0](), OP_LSQ_store, sv0, ROBtag[0](),
                             rtag[2](), ROBtag[1](), 0);
            holder->lsq.push(LSQindex[1](), OP_LSQ_store, sv1, ROBtag[0](),
                             rtag[2](), ROBtag[2](), 1);
            holder->lsq.push(LSQindex[2](), OP_LSQ_store, sv2, ROBtag[0](),
                             rtag[2](), ROBtag[3](), 2);
            holder->lsq.push(LSQindex[3](), OP_LSQ_store, sv3, ROBtag[0](),
                             rtag[2](), ROBtag[4](), 3);
            break;
        default:
            throw "unexpected error in issue LSQ store";
        }
        holder->rob.push(ROBindex[0](), OP_ROB_TMP, 0, ROBtag[0]());
        for (word i = 1; i < pushNum(); i++) {
            holder->rob.push(ROBindex[i](), OP_ROB_MEM, 0, ROBtag[i]());
        }
        break;
    default:
        throw "unexpected error in issue LSQ";
    }
    if (pushNum())
        holder->rob.tlAdd.add(pushNum());
}