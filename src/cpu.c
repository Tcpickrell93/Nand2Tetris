#include "cpu.h"
#include "logic_gates.h"
#include "memory.h"


union bit1_u* Jump(struct jump_flags_s *j_flags) {
    union bit1_u j1 = { .value = j_flags->j1 };
    union bit1_u j2 = { .value = j_flags->j2 };
    union bit1_u j3 = { .value = j_flags->j3 };
    union bit1_u ng = { .value = j_flags->ng };
    union bit1_u zr = { .value = j_flags->zr };
    union bit1_u zero = { .value = 0 };
    union bit1_u one = { .value = 1 };
    union bit1_u or_ng_zr = { .value = 0 };
    Or(&ng, &zr, &or_ng_zr);
    union bit1_u not_or_ng_zr = { .value = 0 };
    Not(&or_ng_zr, &not_or_ng_zr);
    union bit1_u not_ng = { .value = 0 };
    Not(&ng, &not_ng);
    union bit1_u not_zr = { .value = 0 };
    Not(&zr, &not_zr);
    return Mux(Mux(Mux(&zero,
                       &not_or_ng_zr,
                       &j3),
                   Mux(&zr,
                       &not_ng,
                       &j3),
                   &j2),
               Mux(Mux(&ng,
                       &not_zr,
                       &j3),
                   Mux(&or_ng_zr,
                       &one,
                       &j3),
                   &j2),
               &j1);
}

void UpdateCPU(struct CPU *cpu, 
               union byte2_u *inM,
               union byte2_u *instruction,
               union bit1_u *reset,
               union byte2_u *outM, 
               union bit1_u *writeM, 
               union byte2_u *addressM) {
    // if inst_15 == 0, do not perform ALU calculations
    union bit1_u ng = { .value = 0 };
    union bit1_u zr = { .value = 0 };
    union bit1_u zero = { .value = 0 };
    union bit1_u inst_0 = { .value = instruction->byte2_s.val0 };
    union bit1_u inst_1 = { .value = instruction->byte2_s.val1 };
    union bit1_u inst_2 = { .value = instruction->byte2_s.val2 };
    union bit1_u inst_3 = { .value = instruction->byte2_s.val3 };
    union bit1_u inst_4 = { .value = instruction->byte2_s.val4 };
    union bit1_u inst_5 = { .value = instruction->byte2_s.val5 };
    union bit1_u inst_6 = { .value = instruction->byte2_s.val6 };
    union bit1_u inst_7 = { .value = instruction->byte2_s.val7 };
    union bit1_u inst_8 = { .value = instruction->byte2_s.val8 };
    union bit1_u inst_9 = { .value = instruction->byte2_s.val9 };
    union bit1_u inst_10 = { .value = instruction->byte2_s.val10 };
    union bit1_u inst_11 = { .value = instruction->byte2_s.val11 };
    union bit1_u inst_12 = { .value = instruction->byte2_s.val12 };
    union bit1_u inst_13 = { .value = instruction->byte2_s.val13 };
    union bit1_u inst_14 = { .value = instruction->byte2_s.val14 };
    union bit1_u inst_15 = { .value = instruction->byte2_s.val15 };

    ALU(&cpu->reg_D,
        Mux16(&cpu->reg_A,
              inM, 
              &inst_12),
        Mux(&zero, &inst_11, &inst_15),
        Mux(&zero, &inst_10, &inst_15),
        Mux(&zero, &inst_9, &inst_15),
        Mux(&zero, &inst_8, &inst_15),
        Mux(&zero, &inst_7, &inst_15),
        Mux(&zero, &inst_6, &inst_15),
        &zr,
        &ng,
        outM);

    // if inst_15 == 0, instruction is an address that gets loaded into A register
    // else, instruction is a C-instruction and ALU output gets loaded into A register
    union bit1_u load_a = { .value = 1 };
    UpdateRegister16(&cpu->reg_A, 
                     Mux16(instruction, outM, &inst_15), 
                     Mux(&load_a, &inst_5, &inst_15));

    // if inst_15 == 0, do not update reg_D_
    // else, update reg_D_ if inst_4 == 1
    UpdateRegister16(&cpu->reg_D, 
                     outM, 
                     Mux(&zero, &inst_4, &inst_15));


    // if inst_15 == 0, do not write to memory
    // else, write to memory if instruction[3] == 1
    writeM->value = Mux(&zero, &inst_3, &inst_15)->value;

    // if inst_15 == 0, do not jump
    // else, determine if jump is required
    struct jump_flags_s jump_f = {
        .j1 = inst_2.value,
        .j2 = inst_1.value,
        .j3 = inst_0.value,
        .zr = zr.value,
        .ng = ng.value
    };
    union bit1_u load = { .value = 0 };
    load.value = Mux(&zero,
                     Jump(&jump_f),
                     &inst_15)->value;

    union bit1_u increment = { .value = 0 };
    union bit1_u or_res = { .value = 0 };
    Or(&load, reset, &or_res);
    Not(&or_res, &increment);
    // address of the next instruction
    UpdateProgramCounter(&cpu->pc, 
                         &cpu->reg_A, 
                         &load, 
                         &increment, 
                         reset);

    // address of the selected memory register
    addressM = &cpu->reg_A;
}
