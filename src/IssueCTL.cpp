#include "CPU.hpp"
#include "Issue.hpp"
#include "MyConstAndTypedef.hpp"
#include "Tempor.hpp"
#include <endian.h>
void Issue::IssueCTL() {
    cw op = holder->op.getv();
    cw CLR = holder->CLR.getv();
    cw rd_addr = holder->rd_addr.getv();
    cw rs1_addr = holder->rs1_addr.getv();
    cw rs2_addr = holder->rs2_addr.getv();
    cw imm = holder->imm.getv();
    cw tl = holder->rob.tl.getv();
    cw gene = holder->rob.gene.getv();
    cw PC_guess = holder->PC_guess.getv();
    if (op == OP_CTL_jal || op == OP_CTL_jalr) {
        holder->rob.push(tl, OP_ROB_ALU, rd_addr, ROBtag[0]());
        holder->rat.RATWrite.write(rd_addr, ROBtag[0]());
        holder->rob.push(ROBindex[1](), OP_ROB_CTL, PC_guess, ROBtag[1]());
        holder->rob.tlAdd.add(2);
        holder->rs.push(RSindex[0](), OP_ALU_add, ROBtag[0](), rs2_addr, 4, 0,
                        0, 0);
        if (op == OP_CTL_jal)
            holder->rs.push(RSindex[1](), OP_ALU_add, ROBtag[1](), rs2_addr,
                            imm, 0, 0, 0);
        else
            holder->rs.push(RSindex[1](), OP_ALU_add, ROBtag[1](), rval[1](),
                            imm, rtag[1](), 0, 0);
    } else {
        holder->rob.push(tl, OP_ROB_TMP, 0, ROBtag[0]());
        holder->rob.push(ROBindex[1](), OP_ROB_CTL, PC_guess, ROBtag[1]());
        holder->rob.tlAdd.add(2);
        Tempor o;
        switch (op) {
        case OP_CTL_beq:
            o = OP_b_beq;
            break;
        case OP_CTL_bge:
            o = OP_b_bge;
            break;
        case OP_CTL_bgeu:
            o = OP_b_bgeu;
            break;
        case OP_CTL_blt:
            o = OP_b_blt;
            break;
        case OP_CTL_bltu:
            o = OP_b_bltu;
            break;
        }
        o.update();
        holder->rs.push(RSindex[0](), o(), ROBtag[0](), rval[1](), rval[2](),
                        rtag[1](), rtag[2](), 0);
        holder->rs.push(RSindex[1](), OP_b_jump, ROBtag[1](), rd_addr, 0, 0,
                        ROBtag[0](), imm);
    }
}