#include <gtest/gtest.h>
#include <iostream>

extern "C"
{
#include "../src/cpu.h"
#include "../src/machine_language_defines.h"
#include "../src/bits.h"
}


class CPUTest: public ::testing::Test {
    protected:
        CPU cpu = CPU();
        union byte2_u inM = { .value = 0 };
        union bit1_u reset = { .value = 0 };
        union bit1_u writeM = { .value = 0 };
        union byte2_u outM = { .value = 0 };
        union byte2_u addressM = { .value = 0 };

        union byte2_u exp_byte2 = { .value = 0 };

        union byte2_u a_instruction = { .value = 32767 };
        union byte2_u c_instruction = { .value = 0 };
};

TEST_F(CPUTest, A_instruction_test) {
    // Update CPU with A-instruction
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );

    // Make sure register A is set to the A-instruction
    ASSERT_EQ(cpu.reg_A.value, 32767);
}

TEST_F(CPUTest, C_0_test) {
    // Set register A to non-zero
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );

    // Update CPU to set register A to 0
    c_instruction.value = C_0.value | D_A.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );

    // Make sure register A is set to 0
    ASSERT_EQ(cpu.reg_A.value, 0);
}

TEST_F(CPUTest, C_1_test) {
    // Update CPU to set register A to 1
    c_instruction.value = C_1.value | D_A.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 1
    ASSERT_EQ(cpu.reg_A.value, 1);
    // Make sure register D is not 1
    ASSERT_EQ(cpu.reg_D.value, 0);
    // Make sure writeM is 0
    ASSERT_EQ(writeM.value, 0);
}

TEST_F(CPUTest, D_NULL_test) {
    // Update CPU to set Null to 1
    c_instruction.value = C_1.value | D_NULL.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is not 1
    ASSERT_EQ(cpu.reg_A.value, 0);
    // Make sure register D is not 1
    ASSERT_EQ(cpu.reg_D.value, 0);
    // Make sure writeM is 0
    ASSERT_EQ(writeM.value, 0);
}

TEST_F(CPUTest, D_M_test) {
    // Update CPU to set M value to 1
    c_instruction.value = C_1.value | D_M.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is not 1
    ASSERT_EQ(cpu.reg_A.value, 0);
    // Make sure register D is not 1
    ASSERT_EQ(cpu.reg_D.value, 0);
    // Make sure M value is set to 1
    ASSERT_EQ(outM.value, 1);
    // Make sure writeM is set to 1
    ASSERT_EQ(writeM.value, 1);
}

TEST_F(CPUTest, D_D_test) {
    // Update CPU to set register D to 1
    c_instruction.value = C_1.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is not 1
    ASSERT_EQ(cpu.reg_A.value, 0);
    // Make sure register D is set to 1
    ASSERT_EQ(cpu.reg_D.value, 1);
    // Make sure writeM is not 1
    ASSERT_EQ(writeM.value, 0);
}

TEST_F(CPUTest, D_DM_test) {
    // Update CPU to set register D and M value to 1
    c_instruction.value = C_1.value | D_DM.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is not 1
    ASSERT_EQ(cpu.reg_A.value, 0);
    // Make sure register D is set to 1
    ASSERT_EQ(cpu.reg_D.value, 1);
    // Make sure M value is set to 1
    ASSERT_EQ(outM.value, 1);
    // Make sure writeM is set to 1
    ASSERT_EQ(writeM.value, 1);
}

TEST_F(CPUTest, D_AM_test) {
    // Update CPU to set register A and M value to 1
    c_instruction.value = C_1.value | D_AM.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 1
    ASSERT_EQ(cpu.reg_A.value, 1);
    // Make sure register D is not 1
    ASSERT_EQ(cpu.reg_D.value, 0);
    // Make sure M value is set to 1
    ASSERT_EQ(outM.value, 1);
    // Make sure writeM is set to 1
    ASSERT_EQ(writeM.value, 1);
}

TEST_F(CPUTest, D_AD_test) {
    // Update CPU to set register A and register D to 1
    c_instruction.value = C_1.value | D_AD.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 1
    ASSERT_EQ(cpu.reg_A.value, 1);
    // Make sure register D is set to 1
    ASSERT_EQ(cpu.reg_D.value, 1);
    // Make sure writeM is not 1
    ASSERT_EQ(writeM.value, 0);
}

TEST_F(CPUTest, D_ADM_test) {
    // Update CPU to set register A, register D, and M value to 1
    c_instruction.value = C_1.value | D_ADM.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 1
    ASSERT_EQ(cpu.reg_A.value, 1);
    // Make sure register D is set to 1
    ASSERT_EQ(cpu.reg_D.value, 1);
    // Make sure M value is set to 1
    ASSERT_EQ(outM.value, 1);
    // Make sure writeM is set to 1
    ASSERT_EQ(writeM.value, 1);
}

TEST_F(CPUTest, C_NEG_1_test) {
    // Update CPU to set register A to -1
    c_instruction.value = C_NEG_1.value | D_A.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to -1
    ASSERT_EQ(cpu.reg_A.value, 65535);
}

TEST_F(CPUTest, C_D_test) {
    // Update CPU to set register A to -1
    c_instruction.value = C_NEG_1.value | D_A.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register A to register D
    c_instruction.value = C_D.value | D_A.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 0
    ASSERT_EQ(cpu.reg_A.value, 0);
    // Make sure register D is still 0
    ASSERT_EQ(cpu.reg_D.value, 0);
}

TEST_F(CPUTest, C_A_test) {
    // Update CPU to set register A to -1
    c_instruction.value = C_NEG_1.value | D_A.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register A
    c_instruction.value = C_A.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register D is set to -1
    ASSERT_EQ(cpu.reg_D.value, 65535);
    // Make sure register A is still -1
    ASSERT_EQ(cpu.reg_A.value, 65535);
}

TEST_F(CPUTest, C_NOT_D_test) {
    // Update CPU to set register A to not register D
    c_instruction.value = C_NOT_D.value | D_A.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to -1
    ASSERT_EQ(cpu.reg_A.value, 65535);
}

TEST_F(CPUTest, C_NOT_A_test) {
    // Update CPU to set register D to not register A
    c_instruction.value = C_NOT_A.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register D is set to -1
    ASSERT_EQ(cpu.reg_D.value, 65535);
}

TEST_F(CPUTest, C_NEG_D_test) {
    // Update CPU to set register D to 1
    c_instruction.value = C_1.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register A to negative register D
    c_instruction.value = C_NEG_D.value | D_A.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to -1
    ASSERT_EQ(cpu.reg_A.value, 65535);
}

TEST_F(CPUTest, C_NEG_A_test) {
    // Update CPU to set register A to 1
    c_instruction.value = C_1.value | D_A.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to negative register A
    c_instruction.value = C_NEG_A.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register D is set to -1
    ASSERT_EQ(cpu.reg_D.value, 65535);
}

TEST_F(CPUTest, C_D_PLUS_1_test) {
    // Update CPU to set register A to register D plus 1
    c_instruction.value = C_D_PLUS_1.value | D_A.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 1
    ASSERT_EQ(cpu.reg_A.value, 1);
}

TEST_F(CPUTest, C_A_PLUS_1_test) {
    // Update CPU to set register D to register A plus 1
    c_instruction.value = C_A_PLUS_1.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register D is set to 1
    ASSERT_EQ(cpu.reg_D.value, 1);
}

TEST_F(CPUTest, C_D_MINUS_1_test) {
    // Update CPU to set register A to register D minus 1
    c_instruction.value = C_D_MINUS_1.value | D_A.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to -1
    ASSERT_EQ(cpu.reg_A.value, 65535);
}

TEST_F(CPUTest, C_A_MINUS_1_test) {
    // Update CPU to set register D to register A minus 1
    c_instruction.value = C_A_MINUS_1.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register D is set to -1
    ASSERT_EQ(cpu.reg_D.value, 65535);
}

TEST_F(CPUTest, C_D_PLUS_A_test) {
    // Update CPU to set register A and register D to 1
    c_instruction.value = C_1.value | D_AD.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register A to register D plus register A
    c_instruction.value = C_D_PLUS_A.value | D_A.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 2
    ASSERT_EQ(cpu.reg_A.value, 2);
}

TEST_F(CPUTest, C_D_MINUS_A_test) {
    // Update CPU to set register A to 8
    a_instruction.value = 8;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register A
    c_instruction.value = C_A.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register A to 3
    a_instruction.value = 3;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register D minus register A
    c_instruction.value = C_D_MINUS_A.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register D is set to 5
    ASSERT_EQ(cpu.reg_D.value, 5);
}

TEST_F(CPUTest, C_A_MINUS_D_test) {
    // Update CPU to set register A to 3
    a_instruction.value = 3;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register A
    c_instruction.value = C_A.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register A to 8
    a_instruction.value = 8;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register D minus register A
    c_instruction.value = C_A_MINUS_D.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register D is set to 5
    ASSERT_EQ(cpu.reg_D.value, 5);
}

TEST_F(CPUTest, C_D_AND_A_test) {
    // Update CPU to set register A to 3
    a_instruction.value = 3;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register A
    c_instruction.value = C_A.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register A to 7
    a_instruction.value = 7;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register D AND register A
    c_instruction.value = C_D_AND_A.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register D is set to 3
    ASSERT_EQ(cpu.reg_D.value, 3);
}

TEST_F(CPUTest, C_D_OR_A_test) {
    // Update CPU to set register A to 3
    a_instruction.value = 3;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register A
    c_instruction.value = C_A.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register A to 8
    a_instruction.value = 8;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register D OR register A
    c_instruction.value = C_D_OR_A.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register D is set to 11
    ASSERT_EQ(cpu.reg_D.value, 11);
}

TEST_F(CPUTest, C_M_test) {
    // Update CPU to set register A to the value stored in M
    c_instruction.value = C_M.value | D_A.value;
    inM.value = 65535;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 65535
    ASSERT_EQ(cpu.reg_A.value, 65535);
}

TEST_F(CPUTest, C_NOT_M_test) {
    // Update CPU to set register A to not the value stored in M
    c_instruction.value = C_NOT_M.value | D_A.value;
    inM.value = 65535;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 0
    ASSERT_EQ(cpu.reg_A.value, 0);
}

TEST_F(CPUTest, C_NEG_M_test) {
    // Update CPU to set register A to the negative value stored in M
    c_instruction.value = C_NEG_M.value | D_A.value;
    inM.value = 65535;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 1
    ASSERT_EQ(cpu.reg_A.value, 1);
}

TEST_F(CPUTest, C_M_PLUS_1_test) {
    // Update CPU to set register A to the value stored in M minus 1
    c_instruction.value = C_M_PLUS_1.value | D_A.value;
    inM.value = 65535;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 0
    ASSERT_EQ(cpu.reg_A.value, 0);
}

TEST_F(CPUTest, C_M_MINUS_1_test) {
    // Update CPU to set register A to the value stored in M minus 1
    c_instruction.value = C_M_MINUS_1.value | D_A.value;
    inM.value = 65535;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 65534
    ASSERT_EQ(cpu.reg_A.value, 65534);
}

TEST_F(CPUTest, C_D_PLUS_M_test) {
    // Update CPU to set register A to 3
    a_instruction.value = 3;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register A
    c_instruction.value = C_A.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register A to the value stored in M plus D
    c_instruction.value = C_D_PLUS_M.value | D_A.value;
    inM.value = 65535;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 2
    ASSERT_EQ(cpu.reg_A.value, 2);
}

TEST_F(CPUTest, C_D_MINUS_M_test) {
    // Update CPU to set register A to 3
    a_instruction.value = 3;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register A
    c_instruction.value = C_A.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register A to the value stored in D minus M
    c_instruction.value = C_D_MINUS_M.value | D_A.value;
    inM.value = 65535;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 4
    ASSERT_EQ(cpu.reg_A.value, 4);
}

TEST_F(CPUTest, C_M_MINUS_D_test) {
    // Update CPU to set register A to 3
    a_instruction.value = 3;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register A
    c_instruction.value = C_A.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register A to the value stored in M minus D
    c_instruction.value = C_M_MINUS_D.value | D_A.value;
    inM.value = 65535;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 65532
    ASSERT_EQ(cpu.reg_A.value, 65532);
}

TEST_F(CPUTest, C_D_AND_M_test) {
    // Update CPU to set register A to 3
    a_instruction.value = 3;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register A
    c_instruction.value = C_A.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register A to the value stored in M and D
    c_instruction.value = C_D_AND_M.value | D_A.value;
    inM.value = 65535;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 3
    ASSERT_EQ(cpu.reg_A.value, 3);
}

TEST_F(CPUTest, C_D_OR_M_test) {
    // Update CPU to set register A to 3
    a_instruction.value = 3;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register A
    c_instruction.value = C_A.value | D_D.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register A to the value stored in M or D
    c_instruction.value = C_D_OR_M.value | D_A.value;
    inM.value = 65535;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure register A is set to 65535
    ASSERT_EQ(cpu.reg_A.value, 65535);
}

TEST_F(CPUTest, J_NULL_test) {
    // Update CPU to set register A to 3
    a_instruction.value = 3;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register A with no jump
    c_instruction.value = C_A.value | D_D.value | J_NULL.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU does not jump
    ASSERT_EQ(cpu.pc.value, 2);
}

TEST_F(CPUTest, J_JGT_test) {
    // Update CPU to set register A to 3
    a_instruction.value = 3;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register A with jump
    c_instruction.value = C_A.value | D_D.value | J_JGT.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU jumps to address 3
    ASSERT_EQ(cpu.pc.value, 3);
    // Update CPU to set register D to negative register A with jump
    c_instruction.value = C_NEG_A.value | D_D.value | J_JGT.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU does not jump
    ASSERT_EQ(cpu.pc.value, 4);
}

TEST_F(CPUTest, J_JEQ_test) {
    // Update CPU to set register A to 5
    a_instruction.value = 5;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register A with jump
    c_instruction.value = C_A.value | D_D.value | J_JEQ.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU does not jump
    ASSERT_EQ(cpu.pc.value, 2);
    // Update CPU to set register D to 0 with jump
    c_instruction.value = C_0.value | D_D.value | J_JEQ.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU jumps to 5
    ASSERT_EQ(cpu.pc.value, 5);
}

TEST_F(CPUTest, J_JGE_test) {
    // Update CPU to set register A to 5
    a_instruction.value = 5;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to negative register A with jump
    c_instruction.value = C_NEG_A.value | D_D.value | J_JGE.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU does not jump
    ASSERT_EQ(cpu.pc.value, 2);
    // Update CPU to set register D to 0 with jump
    c_instruction.value = C_0.value | D_D.value | J_JGE.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU jumps to 5
    ASSERT_EQ(cpu.pc.value, 5);
    // Update CPU to set register A to 8
    a_instruction.value = 8;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to A with jump
    c_instruction.value = C_A.value | D_D.value | J_JGE.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU jumps to 8
    ASSERT_EQ(cpu.pc.value, 8);
}

TEST_F(CPUTest, J_JLT_test) {
    // Update CPU to set register A to 5
    a_instruction.value = 5;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to 0 with jump
    c_instruction.value = C_0.value | D_D.value | J_JLT.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU does not jump
    ASSERT_EQ(cpu.pc.value, 2);
    // Update CPU to set register D to A with jump
    c_instruction.value = C_A.value | D_D.value | J_JLT.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU does not jump
    ASSERT_EQ(cpu.pc.value, 3);
    // Update CPU to set register D to negative A with jump
    c_instruction.value = C_NEG_A.value | D_D.value | J_JLT.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU jumps to 5
    ASSERT_EQ(cpu.pc.value, 5);
}

TEST_F(CPUTest, J_JNE_test) {
    // Update CPU to set register A to 5
    a_instruction.value = 5;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to 0 with jump
    c_instruction.value = C_0.value | D_D.value | J_JNE.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU does not jump
    ASSERT_EQ(cpu.pc.value, 2);
    // Update CPU to set register D to A with jump
    c_instruction.value = C_A.value | D_D.value | J_JNE.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU jumps to 5
    ASSERT_EQ(cpu.pc.value, 5);
    // Update CPU to set register A to 8
    a_instruction.value = 8;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to negative A with jump
    c_instruction.value = C_NEG_A.value | D_D.value | J_JNE.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU jumps to 8
    ASSERT_EQ(cpu.pc.value, 8);
}

TEST_F(CPUTest, J_JLE_test) {
    // Update CPU to set register A to 5
    a_instruction.value = 5;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register A with jump
    c_instruction.value = C_A.value | D_D.value | J_JLE.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU does not jump
    ASSERT_EQ(cpu.pc.value, 2);
    // Update CPU to set register D to 0 with jump
    c_instruction.value = C_0.value | D_D.value | J_JLE.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU jumps to 5
    ASSERT_EQ(cpu.pc.value, 5);
    // Update CPU to set register A to 8
    a_instruction.value = 8;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to negative A with jump
    c_instruction.value = C_NEG_A.value | D_D.value | J_JLE.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU jumps to 8
    ASSERT_EQ(cpu.pc.value, 8);
}

TEST_F(CPUTest, J_JMP_test) {
    // Update CPU to set register A to 5
    a_instruction.value = 5;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to register A with jump
    c_instruction.value = C_A.value | D_D.value | J_JMP.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU does jumps to 5
    ASSERT_EQ(cpu.pc.value, 5);
    // Update CPU to set register A to 12
    a_instruction.value = 12;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to 0 with jump
    c_instruction.value = C_0.value | D_D.value | J_JMP.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU jumps to 12
    ASSERT_EQ(cpu.pc.value, 12);
    // Update CPU to set register A to 8
    a_instruction.value = 8;
    UpdateCPU(
        &cpu,
        &inM,
        &a_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Update CPU to set register D to negative A with jump
    c_instruction.value = C_NEG_A.value | D_D.value | J_JMP.value;
    UpdateCPU(
        &cpu,
        &inM,
        &c_instruction,
        &reset,
        &outM,
        &writeM,
        &addressM
    );
    // Make sure the CPU jumps to 8
    ASSERT_EQ(cpu.pc.value, 8);
}
