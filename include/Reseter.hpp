#pragma once
#include "MyClass.hpp"
class Reseter : public Module {
  public:
    Reseter(CPU *_);
    void run();
    void update();
};