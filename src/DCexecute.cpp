#include "CPU.hpp"
void CPU::Decode::DCexecute() {
    switch (opcode()) {
    case 0x0:
        return DCnop();
    case 0x33:
    case 0x13:
        return DCALU();
    case 0x03:
    case 0x23:
        return DCMA();
    case 0x67:
    case 0x63:
    case 0x6f:
        return DCCTL();
    case 0x17:
    case 0x37:
        return DCother();
    case 0x73:
        throw "abandoned instruction!";
    default:
        throw "invalid instruction!";
    }
}