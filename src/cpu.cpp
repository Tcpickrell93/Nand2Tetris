#include "cpu.h"
#include "logic_gates.h"


void CPU::Update(const byte2& inM, const byte2& instruction, const bit& reset,
                 byte2& outM, bit& writeM, byte2& addressM, byte2& pc) {
    reg_A_.Update(Mux16(instruction, outM, instruction[0]), instruction[10]);
    reg_D_.Update(outM, instruction[11]);
    writeM = instruction[12];
    outM = ALU(reg_D_.Out(),
               Mux16(reg_A_.Out(), inM, instruction[4]),
               instruction[4],
               instruction[5],
               instruction[6],
               instruction[7],
               instruction[8],
               instruction[9]);
}
