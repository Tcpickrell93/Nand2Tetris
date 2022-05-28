#include "../src/program_counter.h"

#include <gtest/gtest.h>
#include <iostream>


class ProgramCounterTest: public ::testing::Test {
    protected:
        ProgramCounter counter = ProgramCounter();

        const bit load_1 { 0b1u };
        const bit load_0 { 0b0u };

        const bit reset_1 { 0b1u };
        const bit reset_0 { 0b0u };

        const bit increment_1 { 0b1u };
        const bit increment_0 { 0b0u };

        const byte2 in16_1s { 0b1111'1111'1111'1111u };
        const byte2 in16_0s { 0b0000'0000'0000'0000u };
};

TEST_F(ProgramCounterTest, increment_test) {
    // initial parameter values
    counter.Update(in16_1s, load_0, increment_0, reset_0);
    byte2 result { counter.Out() };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);

    // increment the counter
    counter.Update(in16_0s, load_0, increment_1, reset_0);
    result = counter.Out();
    expected = 0b0000'0000'0000'0001u; 
    ASSERT_EQ(result, expected);
}

TEST_F(ProgramCounterTest, reset_test) {
    // increment the counter
    counter.Update(in16_0s, load_0, increment_1, reset_0);
    byte2 result { counter.Out() };
    // make sure value is non-zero
    byte2 expected { 0b0000'0000'0000'0001u }; 
    ASSERT_EQ(result, expected);
    // reset the counter
    counter.Update(in16_1s, load_0, increment_0, reset_1);
    result = counter.Out();
    expected = 0b0000'0000'0000'0000u; 
    ASSERT_EQ(result, expected);
}

TEST_F(ProgramCounterTest, load_test) {
    // load value into counter
    counter.Update(in16_1s, load_1, increment_0, reset_0);
    byte2 result { counter.Out() };
    byte2 expected { 0b1111'1111'1111'1111u };
    ASSERT_EQ(result, expected);
}
