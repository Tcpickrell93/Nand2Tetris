#include "program_counter.h"
#include "arithmetic_chips.h"
#include "logic_gates.h"
#include "memory.h"


void UpdateProgramCounter(ProgramCounter& pc, 
                          const byte2_u& in, 
                          const bit1_u& load, 
                          const bit1_u& increment, 
                          const bit1_u& reset) {
    byte2_u zero { .value = 0 };
    bit1_u one { .value = 1 };
    UpdateRegister16(pc.reg, 
                     Mux16(Mux16(Mux16(pc.reg.r16_s.dff16,
                                       Inc16(pc.reg.r16_s.dff16),
                                       increment),
                                 in,
                                 load),
                           zero,
                           reset),
                     one);
}
