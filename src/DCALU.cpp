#include "CPU.hpp"
void CPU::Decode::DCALU() {
    if (opcode() == 0x33) {
        imm = 0;
    } else {
        switch (funct3()) {
        case 0x1:
        case 0x5:
            imm = imm_IS();
            break;
        default:
            imm = imm_I();
        }
    }
    rd_addr = _rd_addr();
    rs1_addr = _rs1_addr();
    if (opcode() == 0x33)
        rs2_addr = _rs2_addr();
    else {
        rs2_addr = NOT_A_REG_ADDR;
    }
    switch (funct3()) {
    case 0x0:
        if (funct7() == 0x20 && opcode() == 0x33)
            op = OP_ALU_sub;
        else
            op = OP_ALU_add;
        break;
    case 0x7:
        op = OP_ALU_and;
        break;
    case 0x6:
        op = OP_ALU_or;
        break;
    case 0x4:
        op = OP_ALU_xor;
        break;
    case 0x1:
        op = OP_ALU_sll;
        break;
    case 0x5:
        if (funct7() == 0x20) {
            op = OP_ALU_sra;
        } else {
            op = OP_ALU_srl;
        }
        break;
    case 0x2:
        op = OP_ALU_slt;
        break;
    case 0x3:
        op = OP_ALU_sltu;
        break;
    default:
        throw "invalid calculate!";
    }
}