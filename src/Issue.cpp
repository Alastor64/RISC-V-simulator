#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
#include "Tempor.hpp"
Issue::Issue(CPU *_) : Module(_) {}
void Issue::run() {
    cw op = holder->op.getv();
    cw CLR = holder->CLR.getv();
    cw rd_addr = holder->rd_addr.getv();
    cw rs1_addr = holder->rs1_addr.getv();
    cw rs2_addr = holder->rs2_addr.getv();
    cw imm = holder->imm.getv();
    cw tl = holder->rob.tl.getv();
    cw gene = holder->rob.gene.getv();
    cw PC_guess = holder->PC_guess.getv();
    for (word i = 0; i < MAX_ROB_PUSH; i++) {
        cw index = ((tl + i) & getLF1(ROB_SIZE_WIDTH));
        ptl[i] = index;
        tag[i] = make_ROB_tag(index, gene, tl);
    }
    if (op == OP_ALU_nop || CLR == CLEAR_FLAG) {
        return;
    } else {
        switch (op) {
        case OP_ALU_add:
        case OP_ALU_sub:
        case OP_ALU_and:
        case OP_ALU_or:
        case OP_ALU_xor:
        case OP_ALU_sll:
        case OP_ALU_srl:
        case OP_ALU_sra:
        case OP_ALU_slt:
        case OP_ALU_sltu:
        case OP_other_auipc:
        case OP_other_lui:
            holder->rob.push(tl, OP_ROB_ALU, rd_addr, tag[0]());
            holder->rob.tlAdd.add(1);
            holder->rat.RATOr.write(rd_addr, tag[0]());
            break;
        case OP_CTL_beq:
        case OP_CTL_bge:
        case OP_CTL_bgeu:
        case OP_CTL_blt:
        case OP_CTL_bltu:
        case OP_CTL_bne:
            holder->rob.push(tl, OP_ROB_CTL, PC_guess, tag[0]());
            holder->rob.tlAdd.add(1);
            break;
        case OP_CTL_jal:
        case OP_CTL_jalr:
            holder->rob.push(tl, OP_ROB_ALU, rd_addr, tag[0]());
            holder->rat.RATOr.write(rd_addr, tag[0]());
            holder->rob.push(ptl[1](), OP_ROB_CTL, PC_guess, tag[1]());
            holder->rob.tlAdd.add(2);
            break;
        case OP_LSQ_lb:
        case OP_LSQ_lbu:
        case OP_LSQ_lh:
        case OP_LSQ_lhu:
        case OP_LSQ_lw:
        case OP_LSQ_sb:
        case OP_LSQ_sh:
        case OP_LSQ_sw:
            IssueLSQ();
            break;
        case OP_ROB_TMN:
            holder->rob.push(tl, OP_ROB_TMN, 0, tag[0]());
            holder->rob.tlAdd.add(1);
            break;
        default:
            throw "unexpected error in issue";
        }
    }
}
void Issue::update() {
    for (word i = 0; i < MAX_ROB_PUSH; i++) {
        tag[i].update();
        ptl[i].update();
    }
}