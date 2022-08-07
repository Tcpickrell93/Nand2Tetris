#include "program_counter.h"
#include "arithmetic_chips.h"
#include "logic_gates.h"
#include "memory.h"


void UpdateProgramCounter(ProgramCounter *pc, 
                          union byte2_u *in, 
                          union bit1_u *load, 
                          union bit1_u *increment, 
                          union bit1_u *reset) {
    union byte2_u zero = { .value = 0 };
    union bit1_u one = { .value = 1 };
    union byte2_u inc_res = Inc16(pc);
    UpdateRegister16(
        pc, 
        Mux16(Mux16(Mux16(pc,
                          &inc_res,
                          increment
                    ),
                    in,
                    load
              ),
              &zero,
              reset
        ),
        &one
    );
}
