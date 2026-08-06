#pragma once
#include "MyClass.hpp"
#include "Tempor.hpp"
class Issue : public Module {
#ifdef DEBUG
  public:
#else
  private:
#endif
    void IssueLSQ();
    Tempor tag[MAX_ROB_PUSH], ptl[MAX_ROB_PUSH];

  public:
    Issue(CPU *_);
    void run();
    void update();
};