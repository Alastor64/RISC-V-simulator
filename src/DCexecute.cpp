#include "Decode.hpp"
void Decode::DCexecute() {
    switch (opcode()) {
    case 0x0:
        DCnop();
        break;
    case 0x33:
    case 0x13:
        DCALU();
        break;
    case 0x03:
    case 0x23:
        DCMA();
        break;
    case 0x67:
    case 0x63:
    case 0x6f:
        DCCTL();
        break;
    case 0x17:
    case 0x37:
        DCother();
        break;
    // case 0x73:
    //     throw "abandoned instruction!";
    default:
        DCnop();
        break;
    }
}