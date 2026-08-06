#pragma once
#include "MyConstAndTypedef.hpp"
#include <map>
class Register {
#ifdef DEBUG
  public:
#else
  private:
#endif
    word val;
    word tmp;
    bool written;

  public:
    Register();
    void update();
    word getv() const;
    void write(const word &v);
};
class Memory {
#ifdef DEBUG
  public:
#else
  private:
#endif
    std::map<word, byte> val;

  public:
    void write_byte(const word &w, const word &addr);
    // void write_half_word(const word &w, const word &addr);
    // void write_word(const word &w, const word &addr);
    // word get_word(const word &addr);
    word get_byte(const word &addr);
    // word get_signed_byte(const word &addr);
    // word get_half_word(const word &addr);
    // word get_signed_half_word(const word &addr);
    void loadInstruction();
    Memory();
};