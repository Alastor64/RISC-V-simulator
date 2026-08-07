#pragma once
#include "Decode.hpp"
#include "Fetch.hpp"
#include "Issue.hpp"
#include "LSQ.hpp"
#include "Memory.hpp"
#include "MyConstAndTypedef.hpp"
#include "Port.hpp"
#include "RAT.hpp"
#include "ROB.hpp"
#include "RS.hpp"
#include "Reseter.hpp"
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

    Fetch fetch;
    BranchPrediction BP;
    Reseter reseter;
    Decode decode;
    Issue issue;
    RAT rat;
    ROB rob;
    RS rs;
    LSQ lsq;
};