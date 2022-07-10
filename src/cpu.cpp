#include "cpu.h"
#include "logic_gates.h"

#include <iostream>


bit1_u CPU::Jump(const jump_flags_s& j_flags)
{
    bit1_u j1 { j_flags.j1 };
    bit1_u j2 { j_flags.j2 };
    bit1_u j3 { j_flags.j3 };
    bit1_u ng { j_flags.ng };
    bit1_u zr { j_flags.zr };
    bit1_u zero { 0 };
    bit1_u one { 1 };
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

void CPU::Update(const byte2_u& inM,
                 const byte2_u& instruction,
                 const bit1_u& reset,
                 byte2_u& outM, 
                 bit1_u& writeM, 
                 byte2_u& addressM)
{
    //std::cout << "OutM before: " << outM << std::endl;

    // if instruction[15] == 0, do not perform ALU calculations
    bit1_u ng {};
    bit1_u zr {};
    bit1_u zero { 0 };
    bit1_u inst_0 { instruction.byte2_s.val0 };
    bit1_u inst_1 { instruction.byte2_s.val1 };
    bit1_u inst_2 { instruction.byte2_s.val2 };
    bit1_u inst_3 { instruction.byte2_s.val3 };
    bit1_u inst_4 { instruction.byte2_s.val4 };
    bit1_u inst_5 { instruction.byte2_s.val5 };
    bit1_u inst_6 { instruction.byte2_s.val6 };
    bit1_u inst_7 { instruction.byte2_s.val7 };
    bit1_u inst_8 { instruction.byte2_s.val8 };
    bit1_u inst_9 { instruction.byte2_s.val9 };
    bit1_u inst_10 { instruction.byte2_s.val10 };
    bit1_u inst_11 { instruction.byte2_s.val11 };
    bit1_u inst_12 { instruction.byte2_s.val12 };
    bit1_u inst_13 { instruction.byte2_s.val13 };
    bit1_u inst_14 { instruction.byte2_s.val14 };
    bit1_u inst_15 { instruction.byte2_s.val15 };

    outM = ALU(reg_D_.Out(),
               Mux16(reg_A_.Out(),
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

    //std::cout << "OutM after: " << outM << std::endl;

    //std::cout << "Register A before: " << reg_A_.Out() << std::endl;

    // if instruction[15] == 0, instruction is an address that gets loaded into A register
    // else, instruction is a C-instruction and ALU output gets loaded into A register
    bit1_u load_a { 1 };
    reg_A_.Update(Mux16(instruction, outM, inst_15),
                  Mux(load_a, inst_5, inst_15));

    //std::cout << "Register A after: " << reg_A_.Out() << std::endl;

    // if instruction[15] == 0, do not update reg_D_
    // else, update reg_D_ if instruction[4] == 1
    reg_D_.Update(outM,
                  Mux(zero, inst_4, inst_15));

    // if instruction[15] == 0, do not write to memory
    // else, write to memory if instruction[3] == 1
    writeM = Mux(zero, inst_3, inst_15);

    // if instruction[15] == 0, do not jump
    // else, determine if jump is required
    struct jump_flags_s jump_f {};
    jump_f.j1 = inst_2.bit1;
    jump_f.j2 = inst_1.bit1;
    jump_f.j3 = inst_0.bit1;
    jump_f.ng = ng.bit1;
    jump_f.zr = zr.bit1;
    bit1_u load = Mux(zero,
                      Jump(jump_f),
                      inst_15);

    bit1_u increment = Not(Or(load, reset));
    // address of the next instruction
    pc_.Update(reg_A_.Out(),
               load,
               increment,
               reset);

    // address of the selected memory register
    addressM = reg_A_.Out();
}

byte2_u CPU::Get_reg_A() {
    return reg_A_.Out();
}

byte2_u CPU::Get_reg_D() {
    return reg_D_.Out();
}

byte2_u CPU::Get_pc() {
    return pc_.Out();
}