#pragma once
#include "MyClass.hpp"
#include "Tempor.hpp"
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
};