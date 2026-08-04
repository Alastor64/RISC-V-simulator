#pragma once
typedef unsigned char byte;
typedef unsigned int word;
typedef const word cw;
#define DEBUG
constexpr word FULL1 = -1;
constexpr int MAX_REG_NUM = 1 << 5;
constexpr word CLEAR_FLAG = 1;
constexpr word TERMINATE = 1;
constexpr word NOT_A_REG_ADDR = MAX_REG_NUM;
constexpr word getLF1(int len) { return FULL1 >> (32 - len); }
constexpr byte CHAR_to_HEX(char c) {
    return (c <= '9' ? c - '0' : c - 'A' + 10);
}
enum OP {
    OP_ALU_nop = 0,
    OP_ALU_add,
    OP_ALU_sub,
    OP_ALU_and,
    OP_ALU_or,
    OP_ALU_xor,
    OP_ALU_sll,
    OP_ALU_srl,
    OP_ALU_sra,
    OP_ALU_slt,
    OP_ALU_sltu,
    OP_CTL_beq,
    OP_CTL_bge,
    OP_CTL_bgeu,
    OP_CTL_blt,
    OP_CTL_bltu,
    OP_CTL_bne,
    OP_CTL_jal,
    OP_CTL_jalr,
};