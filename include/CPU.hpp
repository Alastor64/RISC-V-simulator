#pragma once
#include "Memory.hpp"
#include "MyConstAndTypedef.hpp"
class CPU {
#ifdef DEBUG
  public:
#else
  private:
#endif
    Register reg[MAX_REG_NUM];
    Memory mem;
    Register PC;
    Register CLR;
    Register CLR_ADDR;
    Register blockROB;
    Register blockRS;
    Register blockLSQ;
    Register ins;
    Register ins_PC;
    Register ins_PC_next;
    Register terminate;
    void update();
    class Module {
#ifdef DEBUG
      public:
#else
        protect :
#endif
        CPU *const holder;

      public:
        Module(CPU *_holder);
    };
    class Fetch : public Module {
      public:
        Fetch(CPU *_);
        void run();
        void update();
    } fetch;
    class BranchPrediction : public Module {
      public:
        BranchPrediction(CPU *_);
        void run();
        void update();
    } BP;
    class Reseter : public Module {
        Reseter(CPU *_);
        void run();
        void update();
    };

  public:
    CPU();
    void run();
};