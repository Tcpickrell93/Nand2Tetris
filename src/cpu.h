#ifndef CPU_H
#define CPU_H

#include "memory.h"
#include "arithmetic_chips.h"
#include "program_counter.h"

struct CPU;
bit1_u Jump(const jump_flags_s& j_flags);      // internal function used to determine if jump is requested
void UpdateCPU(CPU& cpu, 
               const byte2_u& inM,
               const byte2_u& instruction,
               const bit1_u& reset,
               byte2_u& outM, 
               bit1_u& writeM, 
               byte2_u& addressM);

#endif // CPU_H
