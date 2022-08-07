#include <gtest/gtest.h>
#include <iostream>

extern "C"
{
#include "../src/program_counter.h"
#include "../src/bits.h"
}

class ProgramCounterTest: public ::testing::Test {
    protected:
        ProgramCounter pc = ProgramCounter();

        union byte2_u in16 = { .value = 0 };
        union bit1_u load = { .value = 0 };
        union bit1_u reset = { .value = 0 };
        union bit1_u increment = { .value = 0 };

        union byte2_u res_byte2 = { .value = 0 };
        union byte2_u* p_res_byte2 = &res_byte2;

        union bit1_u exp_bit1 = { .value = 0 };
        union byte2_u exp_byte2 = { .value = 0 };
};

/* 
-------------------------------------------------------------------------------
                      PROGRAM COUNTER INCREMENT TESTS
-------------------------------------------------------------------------------
*/
TEST_F(ProgramCounterTest, increment_test) {
    // initial parameter values
    ASSERT_EQ(pc.value, exp_byte2.value);
    UpdateProgramCounter(&pc, &in16, &load, &increment, &reset);
    ASSERT_EQ(pc.value, exp_byte2.value);
    
    // increment the counter
    increment.value = 1;
    UpdateProgramCounter(&pc, &in16, &load, &increment, &reset);
    exp_byte2.value = 1;
    ASSERT_EQ(pc.value, exp_byte2.value);
}

TEST_F(ProgramCounterTest, reset_test) {
    // increment the counter
    increment.value = 1;
    UpdateProgramCounter(&pc, &in16, &load, &increment, &reset);
    exp_byte2.value = 1;
    ASSERT_EQ(pc.value, exp_byte2.value);

    // reset the counter
    increment.value = 0;
    reset.value = 1;
    UpdateProgramCounter(&pc, &in16, &load, &increment, &reset);
    exp_byte2.value = 0;
    ASSERT_EQ(pc.value, exp_byte2.value);
}

TEST_F(ProgramCounterTest, load_test) {
    // load value into counter
    load.value = 1;
    in16.value = 10;
    UpdateProgramCounter(&pc, &in16, &load, &increment, &reset);
    exp_byte2.value = 10;
    ASSERT_EQ(pc.value, exp_byte2.value);
}
