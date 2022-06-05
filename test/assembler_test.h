#include "../src/assembler.h"
#include "../src/machine_language_defines.h"
#include "../src/bits.h"

#include <gtest/gtest.h>
#include <iostream>
#include <filesystem>


class AssemblerTest: public ::testing::Test {
    protected:
        std::string dest { "ADM" };
        std::string dest_null { "null" };
        std::string comp { "D+A" };
        std::string comp_0 { "0" };
        std::string jump { "JGT" };
        std::string jump_null { "null" };
        std::map<std::string, int> symbol_table {
            {"STOP", 4},
            {"LOOP", 8},    
        };
        std::string symbol { "STOP" };
};

TEST_F(AssemblerTest, Process_C_instruction_test) {
    std::string result { Assembler::Process_C_instruction(dest, comp, jump) };
    byte2 expected_bin { D_ADM|C_D_PLUS_A|J_JGT };
    std::string expected { expected_bin.to_string() };
    ASSERT_EQ(result, expected);
}

TEST_F(AssemblerTest, Process_L_instruction_test) {
    std::string result { Assembler::Process_L_instruction(symbol, symbol_table) };
    byte2 expected_bin { 0b0000'0000'0000'0100u };
    std::string expected { expected_bin.to_string() };
    ASSERT_EQ(result, expected);
    symbol = "LOOP";
    result = Assembler::Process_L_instruction(symbol, symbol_table);
    expected_bin = 0b0000'0000'0000'1000u;
    expected = expected_bin.to_string();
    ASSERT_EQ(result, expected);
}