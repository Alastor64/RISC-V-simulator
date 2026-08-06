#include "Decode.hpp"
#include "MyConstAndTypedef.hpp"
void Decode::DCother() {
    imm = imm_U();
    rd_addr = _rd_addr();
    rs2_addr = NOT_A_REG_ADDR;
    switch (opcode()) {
    case 0x17:
        rs1_addr = ins_PC();
        op = OP_other_auipc;
        break;
    case 0x37:
        rs1_addr = NOT_A_REG_ADDR;
        op = OP_other_lui;
        break;
    default:
        throw "invalid other op";
    }
}