#pragma once
#include "Memory.hpp"
#include "MyClass.hpp"
#include "MyConstAndTypedef.hpp"
#include "Port.hpp"
#include "Tempor.hpp"
class LSQ : public Module {
#ifdef DEBUG
  public:
#else
  private:
#endif
    // offset在数据就绪后就是垃圾值了
    Register op[LSQ_SIZE], addr[LSQ_SIZE], val[LSQ_SIZE], qa[LSQ_SIZE],
        qv[LSQ_SIZE], target[LSQ_SIZE], offset[LSQ_SIZE], count[LSQ_SIZE];
    FlexTempor CDBflag;
    FlexTempor preEmpty[LSQ_SIZE];
    FlexTempor emptySize;
    FlexTempor frontROB[LSQ_SIZE][LSQ_SIZE + 1];
    FlexTempor ifready[LSQ_SIZE][LSQ_SIZE + 1];
    FlexTempor frontVal[LSQ_SIZE][LSQ_SIZE + 1];

    void countEmpty();
    void readCDB_CM();
    void counting();
    void checkstore();
    void checkload();

  public:
    PortRead opRead;
    PortWrite opWrite;
    PortWrite addrWrite;
    PortWrite valWrite;
    PortWrite qaWrite;
    PortWrite qvWrite;
    PortWrite targetWrite;
    PortWrite offsetWrite;
    PortWrite countWrite;
    void init();
    void pop(cw &i);
    void push(cw &index, cw &_op, cw &_val, cw &_qa, cw &_qv, cw &_target,
              cw &_offset);
    LSQ(CPU *_);
    void run();
    void update();
};