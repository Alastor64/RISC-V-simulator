#pragma once
#include "MyConstAndTypedef.hpp"
class Tempor {
  private:
    word val;
    bool written;

  public:
    Tempor();
    word &operator=(const word &x);
    Tempor &operator=(const Tempor &) = delete;
    word &operator()();
    void update(); // only update function can call it!
    ~Tempor() noexcept(false);
};