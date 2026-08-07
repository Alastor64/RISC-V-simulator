#include "Issue.hpp"
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
    makeindexs();
    checkROBtag();
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
            IssueALU();
            break;
        case OP_CTL_beq:
        case OP_CTL_bge:
        case OP_CTL_bgeu:
        case OP_CTL_blt:
        case OP_CTL_bltu:
        case OP_CTL_bne:
        case OP_CTL_jal:
        case OP_CTL_jalr:
            IssueCTL();
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
            holder->rob.push(tl, OP_ROB_TMN, 0, ROBtag[0]());
            holder->rob.tlAdd.add(1);
            break;
        default:
            throw "unexpected error in issue";
        }
    }
}
void Issue::update() {
    for (word i = 0; i < 3; i++) {
        rval[i].update();
        rtag[i].update();
    }
    for (word i = 0; i < MAX_ROB_PUSH; i++) {
        ROBtag[i].update();
        ROBindex[i].update();
        RSindex[i].update();
    }
}
void Issue::makeindexs() {
    cw tl = holder->rob.tl.getv();
    cw gene = holder->rob.gene.getv();
    for (word i = 0; i < MAX_ROB_PUSH; i++) {
        cw index = ((tl + i) & getLF1(ROB_SIZE_WIDTH));
        ROBindex[i] = index;
        ROBtag[i] = make_ROB_tag(index, gene, tl);
    }
    for (int i = 0; i < MAX_RS_PUSH; i++) {
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