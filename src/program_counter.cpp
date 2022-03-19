#include "program_counter.h"
#include "arithmetic_chips.h"
#include "logic_gates.h"


byte2 ProgramCounter::Update(const byte2& in, const bit& load, const bit& increment, const bit& reset) {
    reg_.Update(
        Mux16(Mux16(Mux16(reg_.Out(),
                          Inc16(reg_.Out()),
                          increment),
                    in,
                    load),
              0b0000'0000'0000'0000u,
              reset),
        0b1u);
    return reg_.Out();
}
