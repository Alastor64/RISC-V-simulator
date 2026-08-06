#pragma once
#include "Memory.hpp"
#include "MyConstAndTypedef.hpp"
#include "Port.hpp"
#include "Tempor.hpp"
class CPU {
#ifdef DEBUG
  public:
#else
  private:
#endif
    Register reg[MAX_REG_NUM];

  public:
    PortWrite regWrite;
    PortRead regRead;
    Memory mem;
    Register PC;
    Register CLR, CLR_ADDR;
    Register blockROB, blockRS, blockLSQ;
    Register terminate;
    Register ins, ins_PC, ins_PC_next;
    Register op, rd_addr, rs1_addr, rs2_addr, imm, PC_guess;
    CPU();
    void init();
    void run();
    void update();
    class Module {
#ifdef DEBUG
      public:
#else
      protected:
#endif
        CPU *const holder;
        Module(CPU *_holder);
    };
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
    } fetch;
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
    } issue;
    class RAT : public Module {
#ifdef DEBUG
      public:
#else
      private:
#endif
        Register tag[MAX_REG_NUM];

      public:
        PortOr RATOr;
        PortRead RATRead;
        RAT(CPU *_);
        void run();
        void update();
    } rat;
    class ROB : public Module {

#ifdef DEBUG
      public:
#else
      private:
#endif
        Register op[ROB_SIZE_WIDTH];
        Register addr[ROB_SIZE_WIDTH];
        Register val[ROB_SIZE_WIDTH];
        Register tag[ROB_SIZE_WIDTH];
        Register ready[ROB_SIZE_WIDTH];
        word pushCount;
        cw maxPushCount;
        Register hd, tl;

      public:
        PortRead tagRead;
        PortRead valRead;
        ROB(CPU *_);
        void push(cw &, cw &, cw &, cw &, cw &);
        void run();
        void update();
    } rob;
};