#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
Issue::Issue(CPU *_) : Module(_) {}
void Issue::run() {
    cw op = holder->op.getv();
    cw CLR = holder->CLR.getv();
    cw rd_addr = holder->rd_addr.getv();
    cw rs1_addr = holder->rs1_addr.getv();
    cw rs2_addr = holder->rs2_addr.getv();
    cw imm = holder->imm.getv();
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
            cw t1 = holder->rat.RATRead.read(rs1_addr);

            break;
        }
    }
}
void Issue::update() {}