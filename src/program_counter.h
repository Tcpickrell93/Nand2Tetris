#ifndef PROGRAM_COUNTER_H
#define PROGRAM_COUNTER_H

#include "memory.h"

struct ProgramCounter;
void UpdateProgramCounter(ProgramCounter& pc, 
                          const byte2_u& in, 
                          const bit1_u& load, 
                          const bit1_u& increment, 
                          const bit1_u& reset);

# endif // PROGRAM_COUNTER_H
