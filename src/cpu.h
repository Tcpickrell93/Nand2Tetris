#ifndef CPU_H
#define CPU_H

#include "memory.h"
#include "arithmetic_chips.h"
#include "program_counter.h"

class CPU {
public:
    void Update(const byte2& inM, const byte2& instruction, const bit& reset,
                byte2& outM, bit& writeM, byte2& addressM, byte2& pc);
private:
   Register16 reg_A_ {};
   Register16 reg_D_ {};

#endif // CPU_H
