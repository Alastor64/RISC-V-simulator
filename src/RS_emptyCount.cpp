#include "MyConstAndTypedef.hpp"
#include "RS.hpp"
void RS::countEmpty() {
    preEmpty[0] = 0;
    for (word i = 0; i < RS_SIZE - 1; i++) {
        preEmpty[i + 1] = preEmpty[i]() + (op[i].getv() == 0);
    }
    emptySize = preEmpty[RS_SIZE - 1]() + (op[RS_SIZE - 1].getv() == 0);
}