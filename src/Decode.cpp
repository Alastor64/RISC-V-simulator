#include "CPU.hpp"
#include "MyConstAndTypedef.hpp"
#include "Tempor.hpp"
CPU::Decode::Decode(CPU *_) : Module(_) {}
void CPU::Decode::update() {
    ins.update();
    ins_PC.update();
    ins_PC_next.update();
    opcode.update();
    tmp.update();
    funct3.update();
    funct7.update();
    imm_B.update();
    imm_J.update();
    imm_I.update();
    imm_IS.update();
    imm_U.update();
    imm_S.update();
    op.update();
    rd_addr.update();
    rs1_addr.update();
    rs2_addr.update();
    imm.update();
    PC_guess.update();
    _rd_addr.update();
    _rs1_addr.update();
    _rs2_addr.update();
}
void CPU::Decode::run() {
    ins = holder->ins.getv();
    ins_PC = holder->ins_PC.getv();
    ins_PC_next = holder->ins_PC_next.getv();
    cw CLR = holder->CLR.getv();

    if (CLR == CLEAR_FLAG) {
        tmp = 0;
    } else {
        tmp = ins();
    }
    PC_guess = ins_PC_next();
    DCdecode();
    if (tmp() == 0x0ff00513) {
        op = OP_ROB_tmn;
        rd_addr = rs1_addr = rs2_addr = NOT_A_REG_ADDR;
        imm = 0;
    } else {
        DCexecute();
    }

    holder->op.write(op());
    holder->rd_addr.write(rd_addr());
    holder->rs1_addr.write(rs1_addr());
    holder->rs2_addr.write(rs2_addr());
    holder->imm.write(imm());
    holder->PC_guess.write(PC_guess());
}
void CPU::Decode::DCnop() {
    rd_addr = rs1_addr = rs2_addr = NOT_A_REG_ADDR;
    imm = 0;
    op = OP_ALU_nop;
}