#ifndef CPU_H
#define CPU_H

#include "memory.h"
#include "arithmetic_chips.h"
#include "program_counter.h"
#include "bits.h"


struct CPU {
    Register16_u reg_A;         // address register
    Register16_u reg_D;         // data register
    ProgramCounter pc;        // address of next instruction
};
union bit1_u* Jump(struct jump_flags_s *j_flags);      // internal function used to determine if jump is requested
void UpdateCPU(struct CPU *cpu, 
               union byte2_u *inM,
               union byte2_u *instruction,
               union bit1_u *reset,
               union byte2_u *outM, 
               union bit1_u *writeM, 
               union byte2_u *addressM);

#endif // CPU_H
