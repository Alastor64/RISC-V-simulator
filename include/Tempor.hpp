#pragma once
#include "MyConstAndTypedef.hpp"
class Tempor {
  private:
    word val;
    bool written;

  public:
    Tempor();
    const word &operator=(const word &x);
    Tempor &operator=(const Tempor &) = delete;
    const word operator()() const;
    void update(); // only update function can call it!
};
class FlexTempor {
  private:
    word val;
    bool written;

  public:
    FlexTempor();
    const word &operator=(const word &x);
    Tempor &operator=(const Tempor &) = delete;
    const word operator()() const;
    void update(); // only update function can call it!
};