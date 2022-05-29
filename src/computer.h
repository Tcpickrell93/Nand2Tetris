#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>

#include "memory.h"
#include "cpu.h"

class Computer {
public:
    void Load_Program(const std::vector<byte2> program_instructions);
    void Run_Program();
    void Reset();
    RAM16k Get_data_mem();
    RAM16k Get_instruction_mem();

private:
    CPU cpu_ {};
    RAM16k instruction_mem_ {};
    RAM16k data_mem_ {};
};

#endif // COMPUTER_H