#include "computer.h"
#include <iterator>


void Computer::Load_Program(byte2 program_instructions[]) {
    int length_of_program { sizeof(program_instructions) / sizeof(program_instructions[0]) };
    for (int i = 0; i < length_of_program; i++) {
        byte2 address { i };
        instruction_mem_.Write(address, program_instructions[i], 0b1u);
    }
};

void Computer::Run_Program() {
    byte2 inM { data_mem_.Read(0b0000'0000'0000'0000u) };
    byte2 instruction { instruction_mem_.Read(0b0000'0000'0000'0000u) };
    bit reset { 0b1u };
    byte2 outM { 0b0000'0000'0000'0000u };
    bit writeM { 0b0u };
    byte2 addressM { 0b0000'0000'0000'0000u };
    byte2 terminating_address { 0b0000'0000'1000'0000u };
    while (cpu_.Get_pc().to_ulong() < terminating_address.to_ulong()) {
        // Update CPU
        cpu_.Update(inM,
                    instruction,
                    reset,
                    outM,
                    writeM,
                    addressM);
        // Update data memory
        data_mem_.Write(addressM, outM, writeM);
        // Get next instruction
        instruction = cpu_.Get_pc();
    }
}