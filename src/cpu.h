#ifndef CPU_H
#define CPU_H

#include "memory.h"
#include "arithmetic_chips.h"
#include "program_counter.h"

class CPU {
public:
   void Update(const byte2_u& inM,              // value stored in selected memory register
               const byte2_u& instruction,      // instruction to execute
               const bit1_u& reset,             // signals whether to continue executing or restarting the program
               byte2_u& outM,                   // output value to write to memory in addressM
               bit1_u& writeM,                  // write enable bit for output to be written
               byte2_u& addressM);              // address in which we want to write to memory
   byte2_u Get_reg_A();
   byte2_u Get_reg_D();
   byte2_u Get_pc();

private:
   bit1_u Jump(const jump_flags_s& j_flags);      // internal function used to determine if jump is requested
   Register16 reg_A_ {};         // address register
   Register16 reg_D_ {};         // data register
   ProgramCounter pc_ {};        // address of next instruction
};

#endif // CPU_H
