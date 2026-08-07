#pragma once
#include "Memory.hpp"
#include "MyClass.hpp"
#include "MyConstAndTypedef.hpp"
#include "Port.hpp"
#include "Tempor.hpp"
class RS : public Module {

#ifdef DEBUG
  public:
#else
  private:
#endif
    FlexTempor CDBflag;
    FlexTempor preEmpty[RS_SIZE];
    FlexTempor emptySize;
    FlexTempor result;
    Register op[RS_SIZE], tag[RS_SIZE], v1[RS_SIZE], v2[RS_SIZE], q1[RS_SIZE],
        q2[RS_SIZE], imm[RS_SIZE];
    void readCDB();
    void ALU();
    void countEmpty();
    void calc(cw &o, cw &r1, cw &r2, cw &r3);

  public:
    PortRead opRead;
    PortWrite opWrite;
    PortWrite tagWrite;
    PortWrite v1Write;
    PortWrite v2Write;
    PortWrite q1Write;
    PortWrite q2Write;
    PortWrite immWrite;
    void push(cw &index, cw &_op, cw &_tag, cw &_v1, cw &_v2, cw &_q1, cw &_q2,
              cw &_imm);
    RS(CPU *_);
    void run();
    void update();
};