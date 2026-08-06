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
    Register CM_tag;
    Register CDB_LSQ_tag, CDB_RS_tag;
    Register CDB_LSQ_val, CDB_RS_val;
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
        Register op[ROB_SIZE];
        Register addr[ROB_SIZE];
        Register val[ROB_SIZE];
        Register tag[ROB_SIZE];
        Register ready[ROB_SIZE];
        void commit();
        void readCDB();
        FlexTempor ifMEM, ifPop;

      public:
        PortROBtl tlAdd;
        PortRead opRead;
        PortRead addrRead;
        PortRead tagRead;
        PortRead valRead;
        PortRead readyRead;
        PortWrite opWrite;
        PortWrite addrWrite;
        PortWrite valWrite;
        PortWrite tagWrite;
        PortWrite readyWrite;
        Register hd, tl;
        Register gene; //[0,3]
        ROB(CPU *_);
        void push(cw &index, cw &_op, cw &_addr, cw &_val, cw &_tag);
        void run();
        void update();
    } rob;
};