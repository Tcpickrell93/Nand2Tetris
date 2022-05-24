#include "../src/cpu.h"
#include "../src/machine_language_defines.h"

#include <gtest/gtest.h>
#include <iostream>


class CPUTest: public ::testing::Test {
    protected:
        CPU cpu = CPU();
        //RAM8 instruction_mem = RAM8();
        //RAM8 data_mem = RAM8();
        
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
    // Make sure A register is set to the A-instruction
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0111'1111'1111'1111u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_0_test) {
    // Set A register to non-zero
    byte2 a_instruction { 0b0111'1111'1111'1111u };
    cpu.Update(inM_0s,
               a_instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set A register to 0
    byte2 instruction { C_0|D_A };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure A register is set to 0
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_1_test) {
    // Update CPU to set A register to 1
    byte2 instruction { C_1|D_A };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure A register is set to 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0001u };
    ASSERT_EQ(result, expected);
    // Make sure D register is not 1
    result = cpu.Get_reg_D();
    expected = 0b0000'0000'0000'0000u;
    ASSERT_EQ(result, expected);
    // Make sure writeM is 0
    bit write_result { writeM };
    bit write_expected { 0b0u };
    ASSERT_EQ(write_result, write_expected);
}

TEST_F(CPUTest, D_NULL_test) {
    // Update CPU to set Null register to 1
    byte2 instruction { C_1|D_NULL };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure A register is not 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
    // Make sure D register is not 1
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
    // Make sure A register is not 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
    // Make sure D register is not 1
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
    // Update CPU to set D register to 1
    byte2 instruction { C_1|D_D };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure A register is not 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
    // Make sure D register is set to 1
    result = cpu.Get_reg_D();
    expected = 0b0000'0000'0000'0001u;
    ASSERT_EQ(result, expected);
    // Make sure writeM is not 1
    bit write_result { writeM };
    bit write_expected { 0b0u };
    ASSERT_EQ(write_result, write_expected);
}

TEST_F(CPUTest, D_DM_test) {
    // Update CPU to set D register and M value to 1
    byte2 instruction { C_1|D_DM };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure A register is not 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
    // Make sure D register is set to 1
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
    // Update CPU to set A register and M value to 1
    byte2 instruction { C_1|D_AM };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure A register is set to 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0001u };
    ASSERT_EQ(result, expected);
    // Make sure D register is not 1
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
    // Update CPU to set A register and D register to 1
    byte2 instruction { C_1|D_AD };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure A register is set to 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0001u };
    ASSERT_EQ(result, expected);
    // Make sure D register is set to 1
    result = cpu.Get_reg_D();
    expected = 0b0000'0000'0000'0001u;
    ASSERT_EQ(result, expected);
    // Make sure writeM is not 1
    bit write_result { writeM };
    bit write_expected { 0b0u };
    ASSERT_EQ(write_result, write_expected);
}

TEST_F(CPUTest, D_ADM_test) {
    // Update CPU to set A register, D register, and M value to 1
    byte2 instruction { C_1|D_ADM };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure A register is set to 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b0000'0000'0000'0001u };
    ASSERT_EQ(result, expected);
    // Make sure D register is set to 1
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
    // Update CPU to set A register to -1
    byte2 instruction { C_NEG_1|D_A };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure A register is set to 1
    byte2 result { cpu.Get_reg_A() };
    byte2 expected { 0b1111'1111'1111'1111u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_D_test) {
    // Update CPU to set A register to -1
    byte2 instruction { C_NEG_1|D_A };
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Update CPU to set A register to D
    instruction = C_D|D_A;
    cpu.Update(inM_0s,
               instruction,
               reset_0,
               outM,
               writeM,
               addressM);
    // Make sure A register is set to 1
    byte2 result { cpu.Get_reg_D() };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
}

TEST_F(CPUTest, C_A_test) {
    
}

TEST_F(CPUTest, C_NOT_D_test) {
    
}

TEST_F(CPUTest, C_NOT_A_test) {
    
}

TEST_F(CPUTest, C_NEG_D_test) {
    
}

TEST_F(CPUTest, C_NEG_A_test) {
    
}

TEST_F(CPUTest, C_D_PLUS_1_test) {
    
}

TEST_F(CPUTest, C_A_PLUS_1_test) {
    
}

TEST_F(CPUTest, C_D_MINUS_1_test) {
    
}

TEST_F(CPUTest, C_A_MINUS_1_test) {
    
}

TEST_F(CPUTest, C_D_PLUS_A_test) {
    
}

TEST_F(CPUTest, C_D_MINUS_A_test) {
    
}

TEST_F(CPUTest, C_A_MINUS_D_test) {
    
}

TEST_F(CPUTest, C_D_AND_A_test) {
    
}

TEST_F(CPUTest, C_D_OR_A_test) {
    
}

TEST_F(CPUTest, C_M_test) {
    
}

TEST_F(CPUTest, C_NOT_M_test) {
    
}

TEST_F(CPUTest, C_NEG_M_test) {
    
}

TEST_F(CPUTest, C_M_MINUS_1_test) {
    
}

TEST_F(CPUTest, C_D_PLUS_M_test) {
    
}

TEST_F(CPUTest, C_D_MINUS_M_test) {
    
}

TEST_F(CPUTest, C_M_MINUS_D_test) {
    
}

TEST_F(CPUTest, C_D_AND_M_test) {
    
}

TEST_F(CPUTest, C_D_OR_M_test) {
    
}

TEST_F(CPUTest, J_NULL_test) {
    
}

TEST_F(CPUTest, J_JGT_test) {
    
}

TEST_F(CPUTest, J_JEQ_test) {
    
}

TEST_F(CPUTest, J_JGE_test) {
    
}

TEST_F(CPUTest, J_JLT_test) {
    
}

TEST_F(CPUTest, J_JNE_test) {
    
}

TEST_F(CPUTest, J_JLE_test) {
    
}

TEST_F(CPUTest, J_JMP_test) {
    
}
