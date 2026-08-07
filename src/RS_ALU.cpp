#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
#include "RS.hpp"
#include "Tempor.hpp"
void RS::ALU() {
    for (word i = 0; i < RS_SIZE; i++) {
        if (q1[i].getv() || q2[i].getv())
            continue;
        if (CDBflag())
            continue;
        CDBflag = 1;
        cw o = op[i].getv(), r1 = v1[i].getv(), r2 = v2[i].getv(),
           r3 = imm[i].getv();
        calc(o, r1, r2, r3);
        holder->CDB_RS_tag.write(tag[i].getv());
        holder->CDB_RS_val.write(result());
        op[i].write(0);
        tag[i].write(0);
        v1[i].write(0);
        v2[i].write(0);
        q1[i].write(0);
        q2[i].write(0);
        imm[i].write(0);
    }
}
void RS::calc(cw &o, cw &r1, cw &r2, cw &r3) {
    switch (o) {
    case OP_ALU_add:
        result = r1 + r2;
        break;
    case OP_ALU_sub:
        result = r1 - r2;
        break;
    case OP_ALU_and:
        result = r1 & r2;
        break;
    case OP_ALU_or:
        result = r1 | r2;
        break;
    case OP_ALU_xor:
        result = r1 ^ r2;
        break;
    case OP_ALU_sll:
        result = r1 << (r2 & getLF1(5));
        break;
    case OP_ALU_srl:
        result = r1 >> (r2 & getLF1(5));
        break;
    case OP_ALU_sra:
        result = int(r1) >> (r2 & getLF1(5));
        break;
    case OP_ALU_slt:
        result = (int(r1) < int(r2) ? 1 : 0);
        break;
    case OP_ALU_sltu:
        result = (r1 < r2 ? 1 : 0);
        break;
    case OP_CTL_beq:
    case OP_CTL_bge:
    case OP_CTL_bgeu:
    case OP_CTL_blt:
    case OP_CTL_bltu:
    case OP_CTL_bne:
        if (r2) {
            result = r1 + r3;
        } else {
            result = r1 + 4;
        }
        break;
    case OP_CTL_jal:
    case OP_CTL_jalr:
        result = r1 + r3;
        break;
    default:
        throw "invalid op in RS calc";
    }
}