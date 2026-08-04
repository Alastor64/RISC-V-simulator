#pragma once
typedef unsigned char byte;
typedef unsigned int word;
#define DEBUG
constexpr word FULL1 = -1;
constexpr int MAX_REG_NUM = 1 << 5;
constexpr word CLEAR_FLAG = 1;
constexpr word TERMINATE = 1;
constexpr word getLF1(int len) { return FULL1 >> (32 - len); }
constexpr byte CHAR_to_HEX(char c) {
    return (c <= '9' ? c - '0' : c - 'A' + 10);
}