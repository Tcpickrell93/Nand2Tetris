#ifndef CPU_H
#define CPU_H

#include "memory.h"
#include "arithmetic_chips.h"
#include "program_counter.h"

class CPU {
public:
   void Update(const byte2& inM,            // value stored in selected memory register
               const byte2& instruction,    // instruction to execute
               const bit& reset,            // signals whether to continue executing or restarting the program
               byte2& outM,                 // output value to write to memory in addressM
               bit& writeM,                 // write enable bit for output to be written
               byte2& addressM);            // address in which we want to write to memory
   byte2 Get_reg_A();
   byte2 Get_reg_D();

private:
   bit Jump(const bit& j1,
            const bit& j2, 
            const bit& j3, 
            const bit& zr, 
            const bit& ng);      // internal function used to determine if jump is requested
   Register16 reg_A_ {};         // address register
   Register16 reg_D_ {};         // data register
   ProgramCounter pc_ {};        // address of next instruction
};

#endif // CPU_H
