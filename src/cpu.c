#include "cpu.h"
#include "logic_gates.h"
#include "memory.h"

#include <iostream>


struct CPU {
   Register16_u reg_A;         // address register
   Register16_u reg_D;         // data register
   ProgramCounter pc;        // address of next instruction
};

bit1_u Jump(const jump_flags_s& j_flags) {
    bit1_u j1 { .value = j_flags.j1 };
    bit1_u j2 { .value = j_flags.j2 };
    bit1_u j3 { .value = j_flags.j3 };
    bit1_u ng { .value = j_flags.ng };
    bit1_u zr { .value = j_flags.zr };
    bit1_u zero { .value = 0 };
    bit1_u one { .value = 1 };
    return Mux(Mux(Mux(zero,
                       Not(Or(ng, zr)),
                       j3),
                   Mux(zr,
                       Not(ng),
                       j3),
                   j2),
               Mux(Mux(ng,
                       Not(zr),
                       j3),
                   Mux(Or(ng, zr),
                       one,
                       j3),
                   j2),
               j1);
}

void UpdateCPU(CPU& cpu, 
               const byte2_u& inM,
               const byte2_u& instruction,
               const bit1_u& reset,
               byte2_u& outM, 
               bit1_u& writeM, 
               byte2_u& addressM) {
    // if inst_15 == 0, do not perform ALU calculations
    bit1_u ng { .value = 0 };
    bit1_u zr { .value = 0 };
    bit1_u zero { .value = 0 };
    bit1_u inst_0 { .value = instruction.byte2_s.val0 };
    bit1_u inst_1 { .value = instruction.byte2_s.val1 };
    bit1_u inst_2 { .value = instruction.byte2_s.val2 };
    bit1_u inst_3 { .value = instruction.byte2_s.val3 };
    bit1_u inst_4 { .value = instruction.byte2_s.val4 };
    bit1_u inst_5 { .value = instruction.byte2_s.val5 };
    bit1_u inst_6 { .value = instruction.byte2_s.val6 };
    bit1_u inst_7 { .value = instruction.byte2_s.val7 };
    bit1_u inst_8 { .value = instruction.byte2_s.val8 };
    bit1_u inst_9 { .value = instruction.byte2_s.val9 };
    bit1_u inst_10 { .value = instruction.byte2_s.val10 };
    bit1_u inst_11 { .value = instruction.byte2_s.val11 };
    bit1_u inst_12 { .value = instruction.byte2_s.val12 };
    bit1_u inst_13 { .value = instruction.byte2_s.val13 };
    bit1_u inst_14 { .value = instruction.byte2_s.val14 };
    bit1_u inst_15 { .value = instruction.byte2_s.val15 };

    outM = ALU(cpu.reg_D.r16_s.dff16,
               Mux16(cpu.reg_A.r16_s.dff16,
                     inM, 
                     inst_12),
               Mux(zero, inst_11, inst_15),
               Mux(zero, inst_10, inst_15),
               Mux(zero, inst_9, inst_15),
               Mux(zero, inst_8, inst_15),
               Mux(zero, inst_7, inst_15),
               Mux(zero, inst_6, inst_15),
               zr,
               ng);

    // if inst_15 == 0, instruction is an address that gets loaded into A register
    // else, instruction is a C-instruction and ALU output gets loaded into A register
    bit1_u load_a { .value = 1 };
    UpdateRegister16(cpu.reg_A, 
                     Mux16(instruction, outM, inst_15), 
                     Mux(load_a, inst_5, inst_15));

    // if inst_15 == 0, do not update reg_D_
    // else, update reg_D_ if inst_4 == 1
    UpdateRegister16(cpu.reg_D, 
                     outM, 
                     Mux(zero, inst_4, inst_15));


    // if inst_15 == 0, do not write to memory
    // else, write to memory if instruction[3] == 1
    writeM = Mux(zero, inst_3, inst_15);

    // if inst_15 == 0, do not jump
    // else, determine if jump is required
    struct jump_flags_s jump_f {
        .j1 = inst_2.value,
        .j2 = inst_1.value,
        .j3 = inst_0.value,
        .zr = zr.value,
        .ng = ng.value
    };
    bit1_u load = Mux(zero,
                      Jump(jump_f),
                      inst_15);

    bit1_u increment = Not(Or(load, reset));
    // address of the next instruction
    UpdateProgramCounter(cpu.pc, 
                         cpu.reg_A.r16_s.dff16, 
                         load, 
                         increment, 
                         reset);

    // address of the selected memory register
    addressM = cpu.reg_A.r16_s.dff16;
}
