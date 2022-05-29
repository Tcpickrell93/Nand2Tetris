#include "../src/computer.h"
//#include "../src/add.cpp"

#include <gtest/gtest.h>
#include <iostream>
#include <vector>


class ComputerTest: public ::testing::Test {
    protected:
        Computer computer = Computer();
        std::vector<byte2> Add_2_and_3_program = {
            0b0000'0000'0000'0010u,     // Set A to 2
            C_A|D_D|J_NULL,             // Set D to A
            0b0000'0000'0000'0011u,     // Set A to 3
            C_D_PLUS_A|D_D|J_NULL,      // Set D to D plus A
            0b0000'0000'0000'0000u,     // Set A to desired destination address
            C_D|D_M|J_NULL,             // Set M to D
            C_0|D_NULL|J_NULL           // increment without doing anything
        };
};

TEST_F(ComputerTest, Load_program_test) {
    std::vector<byte2> test_program = {
        0b0000'0000'1111'0000u,
        0b0000'0000'0000'0000u,
        0b0000'0000'0000'1111u
    };
}

TEST_F(ComputerTest, Add_program_test) {
    computer.Load_Program(Add_2_and_3_program);
    computer.Reset();
    computer.Run_Program();
    // Make sure register A is set to the A-instruction
    byte2 result { computer.Get_data_mem().Read(0b0000'0000'0000'0000u) };
    byte2 expected { 0b0000'0000'0000'0101u };
    ASSERT_EQ(result, expected);
}