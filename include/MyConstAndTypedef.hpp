#pragma once
typedef unsigned char byte;
typedef unsigned int word;
#define DEBUG
constexpr word full1 = -1;
constexpr int maxreg = 1 << 5;
constexpr word getLFull1(int len) { return full1 >> (32 - len); }
constexpr byte CHAR_to_HEX(char c) {
    return (c <= '9' ? c - '0' : c - 'A' + 10);
}