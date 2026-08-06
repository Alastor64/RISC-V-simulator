#include "Decode.hpp"
void Decode::DCdecode() {
    cw L0 = tmp() & getLF1(7);
    cw L1 = tmp() >> 7 & getLF1(5);
    cw L2 = tmp() >> 12 & getLF1(3);
    cw L3 = tmp() >> 15 & getLF1(5);
    cw L4 = tmp() >> 20 & getLF1(5);
    cw L5 = tmp() >> 25 & getLF1(7);
    opcode = L0;
    _rd_addr = L1;
    funct3 = L2;
    _rs1_addr = L3;
    _rs2_addr = L4;
    funct7 = L5;
    cw _imm_I = L5 << 5 | L4;
    imm_IS = L4;
    cw _imm_S = L5 << 5 | L1;
    cw _imm_B = L1 >> 1 << 1 | (L5 & getLF1(6)) << 5 | (L1 & getLF1(1)) << 11 |
                L5 >> 6 << 12;
    imm_U = tmp() >> 12 << 12;
    cw j1 = tmp() >> 12 & getLF1(8);
    cw j2 = tmp() >> 20;
    cw _imm_J = (j2 & getLF1(11)) >> 1 << 1 | (j2 & getLF1(1)) << 11 |
                j1 << 12 | j2 >> 11 << 20;
    imm_I = (_imm_I >> 11) ? (_imm_I | FULL1 << 12) : _imm_I;
    imm_B = (_imm_B >> 12) ? (_imm_B | FULL1 << 13) : _imm_B;
    imm_J = (_imm_J >> 20) ? (_imm_J | FULL1 << 21) : _imm_J;
    imm_S = (_imm_S >> 11) ? (_imm_S | FULL1 << 12) : _imm_S;
}