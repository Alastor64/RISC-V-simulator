#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
void CPU::Decode::DCMA() {
    rs1_addr = _rs1_addr();
    switch (opcode()) {
    case 0x3:
        imm = imm_I();
        rd_addr = _rd_addr();
        rs2_addr = NOT_A_REG_ADDR;
        switch (funct3()) {
        case 0x0:
            op = OP_LSQ_lb;
            break;
        case 0x4:
            op = OP_LSQ_lbu;
            break;
        case 0x1:
            op = OP_LSQ_lh;
            break;
        case 0x5:
            op = OP_LSQ_lhu;
            break;
        case 0x2:
            op = OP_LSQ_lw;
            break;
        default:
            throw "invalid ins in load memory";
        }
        break;
    case 0x23:
        imm = imm_S();
        rd_addr = NOT_A_REG_ADDR;
        rs2_addr = _rs2_addr();
        switch (funct3()) {
        case 0x0:
            op = OP_LSQ_sb;
            break;
        case 0x1:
            op = OP_LSQ_sh;
            break;
        case 0x2:
            op = OP_LSQ_sw;
            break;
        default:
            throw "invalid ins in store memory";
        }
        break;
    default:
        throw "unexpected error in DCMA()";
    }
}