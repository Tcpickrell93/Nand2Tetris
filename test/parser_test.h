#include "../src/parser.h"
#include "../src/machine_language_defines.h"

#include <gtest/gtest.h>
#include <iostream>
#include <filesystem>


class ParserTest: public ::testing::Test {
    protected:
        std::string current_path { std::filesystem::current_path() };
        std::string file_path { current_path + "/programs/add_2_and_3.txt" };
        std::string empty_file_path { current_path + "/programs/emtpy.txt" };
        Parser parser { Parser(file_path) };
};

TEST_F(ParserTest, Has_more_lines_test) {
    // test non-empty file
    bool result { parser.Has_more_lines() };
    bool expected { true };
    ASSERT_EQ(result, expected);
    // test empty file
    parser = Parser(empty_file_path);
    result = parser.Has_more_lines();
    expected = false;
    ASSERT_EQ(result, expected);
}

TEST_F(ParserTest, Advance_test) {
    std::string result { parser.Advance() };
    std::string expected { "@2" };
    ASSERT_EQ(result, expected);
}

TEST_F(ParserTest, Instruction_type_test) {
    std::string line { "@1" };
    instruction_type result { parser.Instruction_type(line) };
    instruction_type expected { A_INSTRUCTION };
    ASSERT_EQ(result, expected);
    line = "(LOOP)";
    result = parser.Instruction_type(line);
    expected = L_INSTRUCTION;
    ASSERT_EQ(result, expected);
    line = "D=D+A";
    result = parser.Instruction_type(line);
    expected = C_INSTRUCTION;
    ASSERT_EQ(result, expected);
}

TEST_F(ParserTest, Symbol_test) {
    std::string line { "@147892" };
    instruction_type instruction { A_INSTRUCTION };
    std::string result { parser.Symbol(line, instruction) };
    std::string expected { "147892" };
    ASSERT_EQ(result, expected);
    line = "(LOOP)";
    instruction = L_INSTRUCTION;
    result = parser.Symbol(line, instruction);
    expected = "LOOP";
    ASSERT_EQ(result, expected);
}

TEST_F(ParserTest, Dest_test) {
    std::string line { "D=D+A;JMP" };
    std::string result { parser.Dest(line) };
    std::string expected { "D" };
    ASSERT_EQ(result, expected);
    line = "ADM=D+A;JMP";
    result = parser.Dest(line);
    expected = "ADM";
    ASSERT_EQ(result, expected);
}   

TEST_F(ParserTest, Comp_test) {
    std::string line { "D=D+A;JMP" };
    std::string result { parser.Comp(line) };
    std::string expected { "D+A" };
    ASSERT_EQ(result, expected);
    line = "D=A;JMP";
    result = parser.Comp(line);
    expected = "A";
    ASSERT_EQ(result, expected);
    line = "D=1;JMP";
    result = parser.Comp(line);
    expected = "1";
    ASSERT_EQ(result, expected);
}   

TEST_F(ParserTest, Jump_test) {
    std::string line { "D=D+A;JMP" };
    std::string result { parser.Jump(line) };
    std::string expected { "JMP" };
    ASSERT_EQ(result, expected);
    line = "D=D+A";
    result = parser.Jump(line);
    expected = "null";
    ASSERT_EQ(result, expected);
    line = "@123";
    result = parser.Jump(line);
    expected = "null";
    ASSERT_EQ(result, expected);
}   