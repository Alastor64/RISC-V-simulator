#pragma once
#include "MyConstAndTypedef.hpp"
template <typename T = word> class Tempor {
  private:
    T val;
    bool written;

  public:
    Tempor() { written = 0; }
    T &operator=(const T &x) {
        if (written) {
            throw "multiply write tempor!";
        }
        written = 1;
        val = x;
        return val;
    }
    T &operator()() {
        if (!written) {
            throw "use null tempor!";
        }
        return val;
    }
    ~Tempor() noexcept(false) {
        if (!written) {
            throw "unused tempor";
        }
    }
};