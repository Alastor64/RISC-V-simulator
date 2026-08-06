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
    FlexTempor pushNum;
    switch (op) {
    case OP_LSQ_lbu:
    case OP_LSQ_lb:
    case OP_LSQ_lh:
    case OP_LSQ_lhu:
    case OP_LSQ_lw:
        switch (op) {
        case OP_LSQ_lbu:
            pushNum = 1 + 1;
            break;
        case OP_LSQ_lb:
            pushNum = 1 + 1 + 1;
            break;
        case OP_LSQ_lh:
            pushNum = 1 + 2 + 1;
            break;
        case OP_LSQ_lhu:
            pushNum = 1 + 2 + 1;
            break;
        case OP_LSQ_lw:
            pushNum = 1 + 4 + 2 + 1;
            break;
        default:
            throw "unexpected error in issue LSQ load";
        }
        for (word i = 0; i < pushNum() - 1; i++) {
            holder->rob.push(ptl[i](), OP_ROB_TMP, 0, tag[i]());
        }
        holder->rob.push(ptl[pushNum() - 1](), OP_ROB_ALU, rd_addr,
                         tag[pushNum() - 1]());
        holder->rat.RATWrite.write(rd_addr, tag[pushNum() - 1]());
        break;
    case OP_LSQ_sb:
    case OP_LSQ_sh:
    case OP_LSQ_sw:
        switch (op) {
        case OP_LSQ_sb:
            pushNum = 1 + 1;
            break;
        case OP_LSQ_sh:
            pushNum = 1 + 2;
            break;
        case OP_LSQ_sw:
            pushNum = 1 + 4;
            break;
        default:
            throw "unexpected error in issue LSQ store";
        }
        holder->rob.push(ptl[0](), OP_ROB_TMP, 0, tag[0]());
        for (word i = 1; i < pushNum(); i++) {
            holder->rob.push(ptl[i](), OP_ROB_MEM, 0, tag[i]());
        }
        break;
    default:
        throw "unexpected error in issue LSQ";
    }
    if (pushNum())
        holder->rob.tlAdd.add(pushNum());
}