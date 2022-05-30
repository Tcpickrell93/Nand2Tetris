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