#pragma once
#include "Memory.hpp"
#include "MyConstAndTypedef.hpp"
#include "Tempor.hpp"
class CPU {
#ifdef DEBUG
  public:
#else
  private:
#endif
    Register reg[MAX_REG_NUM];
    Memory mem;
    Register PC;
    Register CLR, CLR_ADDR;
    Register blockROB, blockRS, blockLSQ;
    Register terminate;
    Register ins, ins_PC, ins_PC_next;
    Register op, rd_addr, rs1_addr, rs2_addr, imm, PC_guess;
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
      public:
        Reseter(CPU *_);
        void run();
        void update();
    } reseter;
    class Decode : public Module {
#ifdef DEBUG
      public:
#else
      private:
#endif
        Tempor ins, ins_PC, ins_PC_next;
        Tempor opcode, tmp, funct3, funct7;
        Tempor imm_B, imm_J, imm_I, imm_IS, imm_U, imm_S;
        Tempor _rd_addr, _rs1_addr, _rs2_addr;
        Tempor op, rd_addr, rs1_addr, rs2_addr, imm, PC_guess;
        void DCdecode();
        void DCexecute();
        void DCALU();
        void DCCTL();
        void DCMA();
        void DCnop();
        void DCother();

      public:
        Decode(CPU *_);
        void run();
        void update();
    } decode;

  public:
    CPU();
    void init();
    void run();
};