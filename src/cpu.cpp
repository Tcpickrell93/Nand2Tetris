#include "cpu.h"
#include "logic_gates.h"


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
    // if instruction[0] == 0, instruction is an address that gets loaded into A register
    // else, instruction is a C-instruction and ALU output gets loaded into A register
    reg_A_.Update(Mux16(instruction,
                        outM, 
                        instruction[0]),
                  instruction[10]);
    // stores ALU output if instruction[11] == 1
    reg_D_.Update(outM,
                  instruction[11]);
    // write enable bit for the output into the selected memory register
    writeM = instruction[12];
    // output of the ALU and entire CPU
    bit ng {};
    bit zr {};
    outM = ALU(reg_D_.Out(),
               Mux16(reg_A_.Out(),
                     inM, 
                     instruction[4]),
               instruction[4],
               instruction[5],
               instruction[6],
               instruction[7],
               instruction[8],
               instruction[9],
               zr,
               ng);
    bit load = Jump(instruction[13],
                    instruction[14],
                    instruction[15],
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
