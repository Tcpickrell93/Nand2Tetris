#ifndef PROGRAM_COUNTER_H
#define PROGRAM_COUNTER_H

#include "memory.h"

typedef Register16_u ProgramCounter;
void UpdateProgramCounter(ProgramCounter *pc, 
                          union byte2_u *in, 
                          union bit1_u *load, 
                          union bit1_u *increment, 
                          union bit1_u *reset);

# endif // PROGRAM_COUNTER_H
