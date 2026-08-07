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
    // offset在数据就绪后被清除
    Register op[LSQ_SIZE], addr[LSQ_SIZE], val[LSQ_SIZE], qa[LSQ_SIZE],
        qv[LSQ_SIZE], target[LSQ_SIZE], offet[LSQ_SIZE], count[LSQ_SIZE];
    FlexTempor CDBflag;
    FlexTempor preEmpty[LSQ_SIZE];
    FlexTempor emptySize;

    void countEmpty();

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
    void push(cw &index, cw &_op, cw &_val, cw &_qa, cw &_qv, cw &_target,
              cw &_offset);
    LSQ(CPU *_);
    void run();
    void update();
};