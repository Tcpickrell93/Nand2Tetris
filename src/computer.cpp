#include "computer.h"
#include <iostream>


void Computer::Load_Program(const std::vector<byte2> program_instructions) {
    //std::cout << "LOAD PROGRAM" << std::endl;
    for (int i = 0; i < program_instructions.size(); i++) {
        byte2 address { i };
        //std::cout << "address: \t\t" << address << std::endl;
        //std::cout << "program instruction: \t" << program_instructions[i] << std::endl;
        instruction_mem_.Write(address, program_instructions[i], 0b1u);
    }
}

void Computer::Run_Program() {
    //std::cout << "RUN PROGRAM" << std::endl;
    byte2 inM { data_mem_.Read(0b0000'0000'0000'0000u) };
    //std::cout << "instruction mem read: " << instruction_mem_.Read(0b0000'0000'0000'0000u) << std::endl;
    byte2 instruction { instruction_mem_.Read(0b0000'0000'0000'0000u) };
    bit reset { 0b0u };
    byte2 outM { 0b0000'0000'0000'0000u };
    bit writeM { 0b0u };
    byte2 addressM { 0b0000'0000'0000'0000u };
    byte2 terminating_address { 0b0000'0000'0000'1000u };
    while (cpu_.Get_pc().to_ulong() < terminating_address.to_ulong()) {
        //std::cout << "instruction address: \t" << cpu_.Get_pc() << std::endl;
        //std::cout << "instruction: \t\t" << instruction << std::endl;
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
        instruction = instruction_mem_.Read(cpu_.Get_pc());
        //std::cout << "OutM: \t\t\t" << outM << std::endl;
        //std::cout << "writeM: \t\t" << writeM << std::endl;
        //std::cout << "addressM: \t\t" << addressM << std::endl;
    }
}

void Computer::Reset() {
    byte2 inM { data_mem_.Read(0b0000'0000'0000'0000u) };
    byte2 instruction { instruction_mem_.Read(0b0000'0000'0000'0000u) };
    bit reset { 0b1u };
    byte2 outM { 0b0000'0000'0000'0000u };
    bit writeM { 0b0u };
    byte2 addressM { 0b0000'0000'0000'0000u };
    // Update CPU
    cpu_.Update(inM,
                instruction,
                reset,
                outM,
                writeM,
                addressM);
    //std::cout << "pc after reset: \t" << cpu_.Get_pc() << std::endl;
}

RAM16k Computer::Get_data_mem() {
    return data_mem_;
}

RAM16k Computer::Get_instruction_mem() {
    return instruction_mem_;
}