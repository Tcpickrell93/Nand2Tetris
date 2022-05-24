#include "cpu.h"
#include "logic_gates.h"

#include <iostream>


bit CPU::Jump(const bit& j1,
              const bit& j2, 
              const bit& j3, 
              const bit& zr, 
              const bit& ng)
{
    return Mux(Mux(Mux(0,
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
                       1,
                       j3),
                   j2),
               j1);
}

void CPU::Update(const byte2& inM,
                 const byte2& instruction,
                 const bit& reset,
                 byte2& outM, 
                 bit& writeM, 
                 byte2& addressM)
{
    //std::cout << "OutM before: " << outM << std::endl;

    // if instruction[15] == 0, do not perform ALU calculations
    bit ng {};
    bit zr {};
    outM = ALU(reg_D_.Out(),
               Mux16(reg_A_.Out(),
                     inM, 
                     instruction[12]),
               Mux(0, instruction[11], instruction[15]),
               Mux(0, instruction[10], instruction[15]),
               Mux(0, instruction[9], instruction[15]),
               Mux(0, instruction[8], instruction[15]),
               Mux(0, instruction[7], instruction[15]),
               Mux(0, instruction[6], instruction[15]),
               zr,
               ng);

    //std::cout << "OutM after: " << outM << std::endl;

    //std::cout << "Register A before: " << reg_A_.Out() << std::endl;

    // if instruction[15] == 0, instruction is an address that gets loaded into A register
    // else, instruction is a C-instruction and ALU output gets loaded into A register
    bit load_a { 0b1u };
    reg_A_.Update(Mux16(instruction, outM, instruction[15]),
                  Mux(load_a, instruction[5], instruction[15]));

    //std::cout << "Register A after: " << reg_A_.Out() << std::endl;

    // if instruction[15] == 0, do not update reg_D_
    // else, update reg_D_ if instruction[4] == 1
    reg_D_.Update(outM,
                  Mux(0, instruction[4], instruction[15]));

    // if instruction[15] == 0, do not write to memory
    // else, write to memory if instruction[3] == 1
    writeM = Mux(0, instruction[3], instruction[15]);

    bit load = Jump(instruction[2],
                    instruction[1],
                    instruction[0],
                    zr,
                    ng);
    bit increment = Not(Or(load, reset));
    // address of the next instruction
    pc_.Update(reg_A_.Out(),
               load,
               increment,
               reset);

    // address of the selected memory register
    addressM = reg_A_.Out();
}

byte2 CPU::Get_reg_A() {
    return reg_A_.Out();
}

byte2 CPU::Get_reg_D() {
    return reg_D_.Out();
}