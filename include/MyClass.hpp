#pragma once
class CPU;
class Module;
class Fetch;
class Module {
#ifdef DEBUG
  public:
#else
  protected:
#endif
    CPU *const holder;
    Module(CPU *_holder);
};