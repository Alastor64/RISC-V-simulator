#include "Memory.hpp"
#include "MyConstAndTypedef.hpp"
#include <iostream>
Register::Register() { written = 0; }
void Register::update() {
    if (written) {
        val = tmp;
        written = 0;
    }
}
word Register::getv() const { return val; }
void Register::write(const word &v) {
    if (written) {
        throw "multiply write register!";
    }
    written = 1;
    tmp = v;
}
Memory::Memory() {}
void Memory::write_byte(const word &w, const word &addr) {
    val[addr] = byte(w & getLF1(8));
}
// void Memory::write_half_word(const word &w, const word &addr) {
//     val[addr] = byte(w & getLF1(8));
//     val[addr + 1] = byte(w >> 8 & getLF1(8));
// }
// void Memory::write_word(const word &w, const word &addr) {
//     val[addr] = byte(w & getLF1(8));
//     val[addr + 1] = byte(w >> 8 & getLF1(8));
//     val[addr + 2] = byte(w >> 16 & getLF1(8));
//     val[addr + 3] = byte(w >> 24 & getLF1(8));
// }
// word Memory::get_word(const word &addr) {
//     return (val[addr] | (val[addr + 1] << 8) | (val[addr + 2] << 16) |
//             (val[addr + 3] << 24));
// }
word Memory::get_byte(const word &addr) { return val[addr]; }
// word Memory::get_signed_byte(const word &addr) {
//     word tmp = get_byte(addr);
//     if (tmp >> 7)
//         tmp |= FULL1 >> 8 << 8;
//     return tmp;
// }
// word Memory::get_half_word(const word &addr) {
//     return val[addr] | val[addr + 1] << 8;
// }
// word Memory::get_signed_half_word(const word &addr) {
//     word tmp = get_half_word(addr);
//     if (tmp >> 15)
//         tmp |= FULL1 >> 16 << 16;
//     return tmp;
// }
void Memory::loadInstruction() {
    std::string stmp;
    word now = 0;
    while (std::cin >> stmp) {
        if (stmp[0] == '@') {
            now = 0;
            for (int i = 1; i <= 8; i++) {
                now = now << 4 | CHAR_to_HEX(stmp[i]);
            }
        } else {
            val[now++] = CHAR_to_HEX(stmp[0]) << 4 | CHAR_to_HEX(stmp[1]);
        }
    }
}