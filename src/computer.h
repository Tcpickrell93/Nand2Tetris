#ifndef COMPUTER_H
#define COMPUTER_H

#include "memory.h"
#include "cpu.h"
#include "add.h"

class Computer {
public:
    void Load_Program(byte2 program_instructions[]);
    void Run_Program();

private:
    CPU cpu_ {};
    RAM16k instruction_mem_ {};
    RAM16k data_mem_ {};
};

#endif // COMPUTER_H