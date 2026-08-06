#include "Tempor.hpp"
#include "MyConstAndTypedef.hpp"
Tempor::Tempor() { written = 0; }
const word &Tempor::operator=(const word &x) {
    if (written) {
        throw "multiply write tempor!";
    }
    written = 1;
    val = x;
    return val;
}
const word Tempor::operator()() const {
    if (!written) {
        throw "use null tempor!";
    }
    return val;
}
void Tempor::update() {
    if (!written) {
        throw "unused tempor";
    }
    written = 0;
}
FlexTempor::FlexTempor() { written = 0; }
const word &FlexTempor::operator=(const word &x) {
    if (written) {
        throw "multiply write tempor!";
    }
    written = 1;
    val = x;
    return val;
}
const word FlexTempor::operator()() const {
    if (!written) {
        return 0;
    }
    return val;
}
void FlexTempor::update() { written = 0; }