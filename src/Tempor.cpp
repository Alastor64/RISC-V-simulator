#include "Tempor.hpp"
Tempor::Tempor() { written = 0; }
const word &Tempor::operator=(const word &x) {
    if (written) {
        throw "multiply write tempor!";
    }
    written = 1;
    val = x;
    return val;
}
const word &Tempor::operator()() const {
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