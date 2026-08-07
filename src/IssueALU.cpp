#include "CPU.hpp"
#include "Issue.hpp"
void Issue::IssueALU() {
    cw op = holder->op.getv();
    cw CLR = holder->CLR.getv();
    cw rd_addr = holder->rd_addr.getv();
    cw rs1_addr = holder->rs1_addr.getv();
    cw rs2_addr = holder->rs2_addr.getv();
    cw imm = holder->imm.getv();
    cw tl = holder->rob.tl.getv();
    cw gene = holder->rob.gene.getv();
    cw PC_guess = holder->PC_guess.getv();

    holder->rob.push(tl, OP_ROB_ALU, rd_addr, ROBtag[0]());
    holder->rob.tlAdd.add(1);
    holder->rat.RATWrite.write(rd_addr, ROBtag[0]());
    if (op == OP_other_auipc) {
        holder->rs.push(RSindex[0](), OP_ALU_add, ROBtag[0](), rs1_addr, imm, 0,
                        0, 0);
    } else if (op == OP_other_lui) {
        holder->rs.push(RSindex[0](), OP_ALU_add, ROBtag[0](), 0, imm, 0, 0, 0);
    } else {
        if (rs2_addr == NOT_A_REG_ADDR)
            holder->rs.push(RSindex[0](), op, ROBtag[0](), rval[1](), imm,
                            rtag[1](), 0, 0);
        else
            holder->rs.push(RSindex[0](), op, ROBtag[0](), rval[1](), rval[2](),
                            rtag[1](), rtag[2](), 0);
    }
}