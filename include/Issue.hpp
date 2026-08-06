#pragma once
#include "MyClass.hpp"
#include "Tempor.hpp"
class Issue : public Module {
#ifdef DEBUG
  public:
#else
  private:
#endif
  public:
    Issue(CPU *_);
    void run();
    void update();
};