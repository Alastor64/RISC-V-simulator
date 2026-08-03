#include "CPU.hpp"
#include <cstdio>
int main() {
    CPU cpu;
    try {
        cpu.run();
    } catch (const char *s) {
        std::printf("%s\n", s);
    }
    return 0;
}