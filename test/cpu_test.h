#include "../src/cpu.h"
#include "../src/machine_language_defines.h"

#include <gtest/gtest.h>
#include <iostream>


class CPUTest: public ::testing::Test {
    protected:
        CPU cpu = CPU();
        const byte2 inM_1s { 0b1111'1111'1111'1111u };
        const byte2 inM_0s { 0b0000'0000'0000'0000u };
        const bit reset_1 { 0b1u };
        const bit reset_0 { 0b0u };
        byte2 outM { 0b0000'0000'0000'0000u };
        bit writeM { 0b0u };
        byte2 addressM { 0b0000'0000'0000'0000u };
};

TEST_F(CPUTest, A_instruction_test) {
    // Update CPU with A-instruction
    byte2 a_instruction { 0b0111'1111'1111'1111u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure register A is set to the A-instruction
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0111'1111'1111'1111u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_0_test) {
    // Set register A to non-zero
    byte2 a_instruction { 0b0111'1111'1111'1111u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register A to 0
    byte2 instruction { C_0|D_A };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure register A is set to 0
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_1_test) {
    // Update CPU to set register A to 1
    byte2 instruction { C_1|D_A };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure register A is set to 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0001u };
    ASSERT_EQ(result, expected);
    // Make sure register D is not 1
    result = cpu.Get_reg_D();
    expected = 0b0000'0000'0000'0000u;
    ASSERT_EQ(result, expected);
    // Make sure writeM is 0
    bit write_result { writeM };
    bit write_expected { 0b0u };
    ASSERT_EQ(write_result, write_expected);
}

TEST_F(CPUTest, D_NULL_test) {
    // Update CPU to set Null to 1
    byte2 instruction { C_1|D_NULL };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure register A is not 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
    // Make sure register D is not 1
    result = cpu.Get_reg_D();
    expected = 0b0000'0000'0000'0000u;
    ASSERT_EQ(result, expected);
    // Make sure writeM is 0
    bit write_result { writeM };
    bit write_expected { 0b0u };
    ASSERT_EQ(write_result, write_expected);
}

TEST_F(CPUTest, D_M_test) {
    // Update CPU to set M value to 1
    byte2 instruction { C_1|D_M };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure register A is not 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
    // Make sure register D is not 1
    result = cpu.Get_reg_D();
    expected = 0b0000'0000'0000'0000u;
    ASSERT_EQ(result, expected);
    // Make sure M value is set to 1
    result = outM;
    expected = 0b0000'0000'0000'0001u;
    ASSERT_EQ(result, expected);
    // Make sure writeM is set to 1
    bit write_result { writeM };
    bit write_expected { 0b1u };
    ASSERT_EQ(write_result, write_expected);
}

TEST_F(CPUTest, D_D_test) {
    // Update CPU to set register D to 1
    byte2 instruction { C_1|D_D };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure register A is not 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
    // Make sure register D is set to 1
    result = cpu.Get_reg_D();
    expected = 0b0000'0000'0000'0001u;
    ASSERT_EQ(result, expected);
    // Make sure writeM is not 1
    bit write_result { writeM };
    bit write_expected { 0b0u };
    ASSERT_EQ(write_result, write_expected);
}

TEST_F(CPUTest, D_DM_test) {
    // Update CPU to set register D and M value to 1
    byte2 instruction { C_1|D_DM };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure register A is not 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
    // Make sure register D is set to 1
    result = cpu.Get_reg_D();
    expected = 0b0000'0000'0000'0001u;
    ASSERT_EQ(result, expected);
    // Make sure M value is set to 1
    result = outM;
    expected = 0b0000'0000'0000'0001u;
    ASSERT_EQ(result, expected);
    // Make sure writeM is set to 1
    bit write_result { writeM };
    bit write_expected { 0b1u };
    ASSERT_EQ(write_result, write_expected);
}

TEST_F(CPUTest, D_AM_test) {
    // Update CPU to set register A and M value to 1
    byte2 instruction { C_1|D_AM };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure register A is set to 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0001u };
    ASSERT_EQ(result, expected);
    // Make sure register D is not 1
    result = cpu.Get_reg_D();
    expected = 0b0000'0000'0000'0000u;
    ASSERT_EQ(result, expected);
    // Make sure M value is set to 1
    result = outM;
    expected = 0b0000'0000'0000'0001u;
    ASSERT_EQ(result, expected);
    // Make sure writeM is set to 1
    bit write_result { writeM };
    bit write_expected { 0b1u };
    ASSERT_EQ(write_result, write_expected);
}

TEST_F(CPUTest, D_AD_test) {
    // Update CPU to set register A and register D to 1
    byte2 instruction { C_1|D_AD };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure register A is set to 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0001u };
    ASSERT_EQ(result, expected);
    // Make sure register D is set to 1
    result = cpu.Get_reg_D();
    expected = 0b0000'0000'0000'0001u;
    ASSERT_EQ(result, expected);
    // Make sure writeM is not 1
    bit write_result { writeM };
    bit write_expected { 0b0u };
    ASSERT_EQ(write_result, write_expected);
}

TEST_F(CPUTest, D_ADM_test) {
    // Update CPU to set register A, register D, and M value to 1
    byte2 instruction { C_1|D_ADM };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure register A is set to 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0001u };
    ASSERT_EQ(result, expected);
    // Make sure register D is set to 1
    result = cpu.Get_reg_D();
    expected = 0b0000'0000'0000'0001u;
    ASSERT_EQ(result, expected);
    // Make sure M value is set to 1
    result = outM;
    expected = 0b0000'0000'0000'0001u;
    ASSERT_EQ(result, expected);
    // Make sure writeM is set to 1
    bit write_result { writeM };
    bit write_expected { 0b1u };
    ASSERT_EQ(write_result, write_expected);
}

TEST_F(CPUTest, C_NEG_1_test) {
    // Update CPU to set register A to -1
    byte2 instruction { C_NEG_1|D_A };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure register A is set to 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b1111'1111'1111'1111u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_D_test) {
    // Update CPU to set register A to -1
    byte2 instruction { C_NEG_1|D_A };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register A to register D
    instruction = C_D|D_A;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure register A is set to 0
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
    // Make sure register D is still 0
    result = cpu.Get_reg_D() ;
    expected = 0b0000'0000'0000'0000u;
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_A_test) {
    // Update CPU to set register A to -1
    byte2 instruction { C_NEG_1|D_A };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register A
    instruction = C_A|D_D;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure register D is set to -1
    byte2 result { cpu.Get_reg_D() };
    byte2 expected { 0b1111'1111'1111'1111u };
    ASSERT_EQ(result, expected);
    // Make sure register A is still -1
    result = cpu.Get_reg_A() ;
    expected = 0b1111'1111'1111'1111u;
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_NOT_D_test) {
    // Update CPU to set register A to not register D
    byte2 instruction { C_NOT_D|D_A };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b1111'1111'1111'1111u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_NOT_A_test) {
    // Update CPU to set register D to not register A
    byte2 instruction { C_NOT_A|D_D };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_D() };
    byte2 expected { 0b1111'1111'1111'1111u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_NEG_D_test) {
    // Update CPU to set register D to 1
    byte2 instruction { C_1|D_D };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register A to negative register D
    instruction = C_NEG_D|D_A;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b1111'1111'1111'1111u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_NEG_A_test) {
    // Update CPU to set register A to 1
    byte2 instruction { C_1|D_A };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to negative register A
    instruction = C_NEG_A|D_D;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_D() };
    byte2 expected { 0b1111'1111'1111'1111u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_D_PLUS_1_test) {
    // Update CPU to set register A to register D plus 1
    byte2 instruction { C_D_PLUS_1|D_A };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0001u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_A_PLUS_1_test) {
    // Update CPU to set register D to register A plus 1
    byte2 instruction { C_A_PLUS_1|D_D };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_D() };
    byte2 expected { 0b0000'0000'0000'0001u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_D_MINUS_1_test) {
    // Update CPU to set register A to register D minus 1
    byte2 instruction { C_D_MINUS_1|D_A };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b1111'1111'1111'1111u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_A_MINUS_1_test) {
    // Update CPU to set register D to register A minus 1
    byte2 instruction { C_A_MINUS_1|D_D };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_D() };
    byte2 expected { 0b1111'1111'1111'1111u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_D_PLUS_A_test) {
    // Update CPU to set register A and register D to 1
    byte2 instruction { C_1|D_AD };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register A to register D plus register A
    instruction = C_D_PLUS_A|D_A;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0010u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_D_MINUS_A_test) {
    // Update CPU to set register A to 8
    byte2 a_instruction { 0b0000'0000'0000'1000u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register A
    byte2 instruction { C_A|D_D };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register A to 3
    a_instruction = 0b0000'0000'0000'0011u;
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register D minus register A
    instruction = C_D_MINUS_A|D_D;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_D() };
    byte2 expected { 0b0000'0000'0000'0101u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_A_MINUS_D_test) {
    // Update CPU to set register A to 3
    byte2 a_instruction { 0b0000'0000'0000'0011u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register A
    byte2 instruction { C_A|D_D };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register A to 8
    a_instruction = 0b0000'0000'0000'1000u;
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register D minus register A
    instruction = C_A_MINUS_D|D_D;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_D() };
    byte2 expected { 0b0000'0000'0000'0101u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_D_AND_A_test) {
    // Update CPU to set register A to 3
    byte2 a_instruction { 0b0000'0000'0000'0011u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register A
    byte2 instruction { C_A|D_D };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register A to 7
    a_instruction = 0b0000'0000'0000'0111u;
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register D AND register A
    instruction = C_D_AND_A|D_D;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_D() };
    byte2 expected { 0b0000'0000'0000'0011u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_D_OR_A_test) {
    // Update CPU to set register A to 3
    byte2 a_instruction { 0b0000'0000'0000'0011u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register A
    byte2 instruction { C_A|D_D };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register A to 8
    a_instruction = 0b0000'0000'0000'1000u;
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register D OR register A
    instruction = C_D_OR_A|D_D;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_D() };
    byte2 expected { 0b0000'0000'0000'1011u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_M_test) {
    // Update CPU to set register A to the value stored in M
    byte2 instruction { C_M|D_A };
    cpu.Update(inM_1s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b1111'1111'1111'1111u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_NOT_M_test) {
    // Update CPU to set register A to not the value stored in M
    byte2 instruction { C_NOT_M|D_A };
    cpu.Update(inM_1s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_NEG_M_test) {
    // Update CPU to set register A to the negative value stored in M
    byte2 instruction { C_NEG_M|D_A };
    cpu.Update(inM_1s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0001u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_M_PLUS_1_test) {
    // Update CPU to set register A to the value stored in M minus 1
    byte2 instruction { C_M_PLUS_1|D_A };
    cpu.Update(inM_1s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_M_MINUS_1_test) {
    // Update CPU to set register A to the value stored in M minus 1
    byte2 instruction { C_M_MINUS_1|D_A };
    cpu.Update(inM_1s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b1111'1111'1111'1110u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_D_PLUS_M_test) {
    // Update CPU to set register A to 3
    byte2 a_instruction { 0b0000'0000'0000'0011u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register A
    byte2 instruction { C_A|D_D };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register A to the value stored in M plus D
    instruction = C_D_PLUS_M|D_A;
    cpu.Update(inM_1s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0010u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_D_MINUS_M_test) {
    // Update CPU to set register A to 3
    byte2 a_instruction { 0b0000'0000'0000'0011u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register A
    byte2 instruction { C_A|D_D };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register A to the value stored in D minus M
    instruction = C_D_MINUS_M|D_A;
    cpu.Update(inM_1s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0100u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_M_MINUS_D_test) {
    // Update CPU to set register A to 3
    byte2 a_instruction { 0b0000'0000'0000'0011u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register A
    byte2 instruction { C_A|D_D };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register A to the value stored in M minus D
    instruction = C_M_MINUS_D|D_A;
    cpu.Update(inM_1s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b1111'1111'1111'1100u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_D_AND_M_test) {
    // Update CPU to set register A to 3
    byte2 a_instruction { 0b0000'0000'0000'0011u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register A
    byte2 instruction { C_A|D_D };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register A to the value stored in M and D
    instruction = C_D_AND_M|D_A;
    cpu.Update(inM_1s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0011u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_D_OR_M_test) {
    // Update CPU to set register A to 3
    byte2 a_instruction { 0b0000'0000'0000'0011u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register A
    byte2 instruction { C_A|D_D };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register A to the value stored in M or D
    instruction = C_D_OR_M|D_A;
    cpu.Update(inM_1s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b1111'1111'1111'1111u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, J_NULL_test) {
    // Update CPU to set register A to 3
    byte2 a_instruction { 0b0000'0000'0000'0011u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register A with no jump
    byte2 instruction { C_A|D_D|J_NULL };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU does not jump
    byte2 result { cpu.Get_pc() };
    byte2 expected { 0b0000'0000'0000'0010u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, J_JGT_test) {
    // Update CPU to set register A to 3
    byte2 a_instruction { 0b0000'0000'0000'0011u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register A with jump
    byte2 instruction { C_A|D_D|J_JGT };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU jumps to address 3
    byte2 result { cpu.Get_pc() };
    byte2 expected { 0b0000'0000'0000'0011u };
    ASSERT_EQ(result, expected);
    // Update CPU to set register D to negative register A with jump
    instruction = C_NEG_A|D_D|J_JGT;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU does not jump
    result = cpu.Get_pc();
    expected = 0b0000'0000'0000'0100u;
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, J_JEQ_test) {
    // Update CPU to set register A to 5
    byte2 a_instruction { 0b0000'0000'0000'0101u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register A with jump
    byte2 instruction { C_A|D_D|J_JEQ };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU does not jump
    byte2 result { cpu.Get_pc() };
    byte2 expected { 0b0000'0000'0000'0010u };
    ASSERT_EQ(result, expected);
    // Update CPU to set register D to 0 with jump
    instruction = C_0|D_D|J_JEQ;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU jumps to 5
    result = cpu.Get_pc();
    expected = 0b0000'0000'0000'0101u;
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, J_JGE_test) {
    // Update CPU to set register A to 5
    byte2 a_instruction { 0b0000'0000'0000'0101u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to negative register A with jump
    byte2 instruction { C_NEG_A|D_D|J_JGE };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU does not jump
    byte2 result { cpu.Get_pc() };
    byte2 expected { 0b0000'0000'0000'0010u };
    ASSERT_EQ(result, expected);
    // Update CPU to set register D to 0 with jump
    instruction = C_0|D_D|J_JGE;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU jumps to 5
    result = cpu.Get_pc();
    expected = 0b0000'0000'0000'0101u;
    ASSERT_EQ(result, expected);
    // Update CPU to set register A to 8
    a_instruction = 0b0000'0000'0000'1000u;
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to A with jump
    instruction = C_A|D_D|J_JGE;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU jumps to 8
    result = cpu.Get_pc();
    expected = 0b0000'0000'0000'1000u;
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, J_JLT_test) {
    // Update CPU to set register A to 5
    byte2 a_instruction { 0b0000'0000'0000'0101u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to 0 with jump
    byte2 instruction { C_0|D_D|J_JLT };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU does not jump
    byte2 result { cpu.Get_pc() };
    byte2 expected { 0b0000'0000'0000'0010u };
    ASSERT_EQ(result, expected);
    // Update CPU to set register D to A with jump
    instruction = C_A|D_D|J_JLT;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU does not jump
    result = cpu.Get_pc();
    expected = 0b0000'0000'0000'0011u;
    ASSERT_EQ(result, expected);
    // Update CPU to set register D to negative A with jump
    instruction = C_NEG_A|D_D|J_JLT;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU jumps to 5
    result = cpu.Get_pc();
    expected = 0b0000'0000'0000'0101u;
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, J_JNE_test) {
    // Update CPU to set register A to 5
    byte2 a_instruction { 0b0000'0000'0000'0101u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to 0 with jump
    byte2 instruction { C_0|D_D|J_JNE };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU does not jump
    byte2 result { cpu.Get_pc() };
    byte2 expected { 0b0000'0000'0000'0010u };
    ASSERT_EQ(result, expected);
    // Update CPU to set register D to A with jump
    instruction = C_A|D_D|J_JNE;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU jumps to 5
    result = cpu.Get_pc();
    expected = 0b0000'0000'0000'0101u;
    ASSERT_EQ(result, expected);
    // Update CPU to set register A to 8
    a_instruction = 0b0000'0000'0000'1000u;
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to negative A with jump
    instruction = C_NEG_A|D_D|J_JNE;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU jumps to 8
    result = cpu.Get_pc();
    expected = 0b0000'0000'0000'1000u;
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, J_JLE_test) {
    // Update CPU to set register A to 5
    byte2 a_instruction { 0b0000'0000'0000'0101u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register A with jump
    byte2 instruction { C_A|D_D|J_JLE };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU does not jump
    byte2 result { cpu.Get_pc() };
    byte2 expected { 0b0000'0000'0000'0010u };
    ASSERT_EQ(result, expected);
    // Update CPU to set register D to 0 with jump
    instruction = C_0|D_D|J_JLE;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU jumps to 5
    result = cpu.Get_pc();
    expected = 0b0000'0000'0000'0101u;
    ASSERT_EQ(result, expected);
    // Update CPU to set register A to 8
    a_instruction = 0b0000'0000'0000'1000u;
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to negative A with jump
    instruction = C_NEG_A|D_D|J_JLE;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU jumps to 8
    result = cpu.Get_pc();
    expected = 0b0000'0000'0000'1000u;
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, J_JMP_test) {
    // Update CPU to set register A to 5
    byte2 a_instruction { 0b0000'0000'0000'0101u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to register A with jump
    byte2 instruction { C_A|D_D|J_JMP };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU does jumps to 5
    byte2 result { cpu.Get_pc() };
    byte2 expected { 0b0000'0000'0000'0101u };
    ASSERT_EQ(result, expected);
    // Update CPU to set register A to 12
    a_instruction = 0b0000'0000'0001'0000u;
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to 0 with jump
    instruction = C_0|D_D|J_JMP;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU jumps to 12
    result = cpu.Get_pc();
    expected = 0b0000'0000'0001'0000u;
    ASSERT_EQ(result, expected);
    // Update CPU to set register A to 8
    a_instruction = 0b0000'0000'0000'1000u;
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set register D to negative A with jump
    instruction = C_NEG_A|D_D|J_JMP;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure the CPU jumps to 8
    result = cpu.Get_pc();
    expected = 0b0000'0000'0000'1000u;
    ASSERT_EQ(result, expected);
}
