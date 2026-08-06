#pragma once
#include "MyClass.hpp"
#include "Tempor.hpp"
class Fetch : public Module {
#ifdef DEBUG
  public:
#else
  private:
#endif
    Tempor ins;

  public:
    Fetch(CPU *_);
    void run();
    void update();
};
class BranchPrediction : public Module {

#ifdef DEBUG
  public:
#else
  private:
#endif
    Tempor ins_PC, ins_PC_next, _PC;

  public:
    BranchPrediction(CPU *_);
    void run();
    void update();
};