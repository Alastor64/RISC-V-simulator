#include "Decode.hpp"
#include "MyConstAndTypedef.hpp"
void Decode::DCCTL() {
    if (opcode() == 0x67) {
        op = OP_CTL_jalr;
        rd_addr = _rd_addr();
        rs1_addr = _rs1_addr();
        rs2_addr = ins_PC();
        imm = imm_I();
        return;
    }
    if (opcode() == 0x6f) {
        op = OP_CTL_jal;
        rd_addr = _rd_addr();
        rs1_addr = NOT_A_REG_ADDR;
        rs2_addr = ins_PC();
        imm = imm_J();
        return;
    }
    imm = imm_B();
    rd_addr = ins_PC();
    rs1_addr = _rs1_addr();
    rs2_addr = _rs2_addr();
    switch (funct3()) {
    case 0x0:
        op = OP_CTL_beq;
        break;
    case 0x5:
        op = OP_CTL_bge;
        break;
    case 0x7:
        op = OP_CTL_bgeu;
        break;
    case 0x4:
        op = OP_CTL_blt;
        break;
    case 0x6:
        op = OP_CTL_bltu;
        break;
    case 0x1:
        op = OP_CTL_bne;
        break;
    default:
        throw "invalid control!";
    }
}