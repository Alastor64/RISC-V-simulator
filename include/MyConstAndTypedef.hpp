#pragma once
typedef unsigned char byte;
typedef unsigned int word;
typedef const word cw;
#define DEBUG
constexpr word memtick = 4;

constexpr word BLOCK_TURN = 5;

constexpr word LSQ_SIZE_WIDTH = 8;
constexpr word LSQ_SIZE = 1 << LSQ_SIZE_WIDTH;
constexpr word MAX_LSQ_PUSH = 4;
constexpr word MAX_LSQ_WRITE_COUNT = MAX_LSQ_PUSH;

constexpr word RS_SIZE_WIDTH = 8;
constexpr word RS_SIZE = 1 << RS_SIZE_WIDTH;
constexpr word MAX_RS_PUSH = 8;
constexpr word MAX_RS_WRITE_COUNT = MAX_RS_PUSH;

constexpr word ROB_SIZE_WIDTH = 8;
constexpr word ROB_SIZE = 1 << ROB_SIZE_WIDTH; //> ROB_SIZE_WIDTH*BLOCK_TURN+1
constexpr word MAX_ROB_PUSH = 8;
constexpr word MAX_ROB_WRITE_COUNT = MAX_ROB_PUSH + 1;

constexpr word FULL1 = -1;
constexpr int MAX_REG_NUM = 1 << 5;
constexpr word CLEAR_FLAG = 1;
constexpr word TERMINATE = 1;
constexpr word NOT_A_REG_ADDR = MAX_REG_NUM;
consteval word getLF1(const int len) { return FULL1 >> (32 - len); }
constexpr byte CHAR_to_HEX(char c) {
    return (c <= '9' ? c - '0' : c - 'A' + 10);
}
constexpr bool inqueue(cw &x, cw &hd, cw &tl) {
    if (hd <= tl) {
        return x >= hd && x < tl;
    } else {
        return x >= hd || x < tl;
    }
}
constexpr word make_ROB_tag(cw &index, cw &gene) {
    return index | gene << ROB_SIZE_WIDTH | 1 << (2 + ROB_SIZE_WIDTH);
}
constexpr word make_ROB_tag(cw &index, cw &gene,
                            cw &tl) { // x must be out of queue
    if (index >= tl)
        return make_ROB_tag(index, gene);
    else
        return make_ROB_tag(index, (gene + 1) & 3);
}
constexpr bool ROByounger(cw &a, cw &b) {
    cw ga = a >> ROB_SIZE_WIDTH & getLF1(2);
    cw gb = b >> ROB_SIZE_WIDTH & getLF1(2);
    cw ia = a & getLF1(ROB_SIZE_WIDTH);
    cw ib = b & getLF1(ROB_SIZE_WIDTH);
    if (ga == gb)
        return ia < ib;
    else {
        if ((ga + 1 & 3) == gb)
            return 1;
        if ((gb + 1 & 3) == ga)
            return 0;
        throw "unexpected error in compare ROB";
    }
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
    OP_LSQ_lb,
    OP_LSQ_lbu,
    OP_LSQ_lh,
    OP_LSQ_lhu,
    OP_LSQ_lw,
    OP_LSQ_sb,
    OP_LSQ_sh,
    OP_LSQ_sw,
    OP_other_auipc,
    OP_other_lui,
    OP_ROB_TMN,
    OP_ROB_ALU,
    OP_ROB_CTL,
    OP_ROB_MEM,
    OP_ROB_TMP,
    OP_load_signed_bit,
    OP_load_link_bit_u,
    OP_load_link_bit,
    OP_load_link_half,
    OP_b_beq,
    OP_b_bge,
    OP_b_bgeu,
    OP_b_blt,
    OP_b_bltu,
    OP_b_bne,
    OP_b_jump,
    OP_LSQ_store,
    OP_LSQ_load,
};