#pragma once
#include "Memory.hpp"
#include "MyConstAndTypedef.hpp"
class PortWrite {
    Register *const file;
    cw size;
    cw maxCount;
    word count;

  public:
    PortWrite(Register *_, cw &_size, cw &_maxCount);
    void write(cw &index, cw &value);
    void update();
};
class PortOr { // 将两个port的结果按位或后输出
    Register *const file;
    cw size;
    word count;
    word index[2];
    word value[2];

  public:
    PortOr(Register *_, cw &_size);
    void write(cw &_index, cw &_value);
    void update();
};
class PortRead {
    Register const *const file;
    cw size;

  public:
    PortRead(Register const *_, cw &size);
    word read(cw &index) const;
    void update();
};
class PortROBtl {
    Register *const tl;
    Register *const gene;
    word count;

  public:
    PortROBtl(Register *_tl, Register *_gene);
    void add(cw &x);
    void update();
};