#pragma once
#include "Memory.hpp"
#include "MyClass.hpp"
#include "Port.hpp"
class RAT : public Module {
#ifdef DEBUG
  public:
#else
  private:
#endif
    Register tag[MAX_REG_NUM];

  public:
    PortRAT RATWrite;
    PortRead RATRead;
    RAT(CPU *_);
    void run();
    void update();
};