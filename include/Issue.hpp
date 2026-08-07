#pragma once
#include "MyClass.hpp"
#include "MyConstAndTypedef.hpp"
#include "Tempor.hpp"
class Issue : public Module {
#ifdef DEBUG
  public:
#else
  private:
#endif
    void IssueLSQ();
    void IssueALU();
    void IssueCTL();
    void checkROBtag();
    void makeindexs();
    Tempor ROBtag[MAX_ROB_PUSH], ROBindex[MAX_ROB_PUSH];
    Tempor RSindex[MAX_RS_PUSH];
    Tempor rval[3], rtag[3];

  public:
    Issue(CPU *_);
    void run();
    void update();
};