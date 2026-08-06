#pragma once
#include "Memory.hpp"
#include "MyClass.hpp"
#include "Port.hpp"
#include "Tempor.hpp"
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
};