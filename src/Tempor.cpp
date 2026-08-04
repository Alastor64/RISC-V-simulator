#include "Tempor.hpp"
Tempor::Tempor() { written = 0; }
word &Tempor::operator=(const word &x) {
    if (written) {
        throw "multiply write tempor!";
    }
    written = 1;
    val = x;
    return val;
}
word &Tempor::operator()() {
    if (!written) {
        throw "use null tempor!";
    }
    return val;
}
Tempor::~Tempor() noexcept(false) {
    if (!written) {
        throw "unused tempor";
    }
};
void Tempor::update() {
    if (!written) {
        throw "unused tempor";
    }
    written = 0;
}