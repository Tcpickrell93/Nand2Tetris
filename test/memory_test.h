#include "../src/memory.h"

#include <gtest/gtest.h>
#include <iostream>


class MemoryTest: public ::testing::Test {
    protected:
        DataFlipFLop dff = DataFlipFLop();
        RegisterBit rb = RegisterBit();
        
        const bit in_1 { 0b1u };
        const bit in_0 { 0b0u };

        const bit load_1 { 0b1u };
        const bit load_0 { 0b0u };

        Register16 r16 = Register16();

        const byte2 in16_1s { 0b1111'1111'1111'1111u };
        const byte2 in16_0s { 0b0000'0000'0000'0000u };
};

TEST_F(MemoryTest, DataFlipFLop_test) {
    // initial parameter values
    bit result { dff.Out() };
    bit expected { 0b0u };
    ASSERT_EQ(result, expected);

    // update bit
    dff.Update(in_1);
    result = dff.Out();
    expected = 0b1u;
    ASSERT_EQ(result, expected);
}

TEST_F(MemoryTest, RegisterBit_test) {
    // initial parameter values
    bit result { rb.Out() };
    bit expected { 0b0u };
    ASSERT_EQ(result, expected);
    
    // in = 1, load = 1
    rb.Update(in_1, load_1);
    result = rb.Out();
    expected = 0b1u;
    ASSERT_EQ(result, expected);

    // in = 0, load = 0
    rb.Update(in_0, load_0);
    result = rb.Out();
    expected = 0b1u;
    ASSERT_EQ(result, expected);

    // in = 0, load = 1
    rb.Update(in_0, load_1);
    result = rb.Out();
    expected = 0b0u;
    ASSERT_EQ(result, expected);
}

TEST_F(MemoryTest, Register16_test) {
    // initial parameter values
    byte2 result { r16.Out() };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);

    // in = 1s, load = 1s
    r16.Update(in16_1s, load_1);
    result = r16.Out();
    expected = 0b1111'1111'1111'1111u;
    ASSERT_EQ(result, expected);

    // in = 0s, load = 0s
    r16.Update(in16_0s, load_0);
    result = r16.Out();
    expected = 0b1111'1111'1111'1111u;
    ASSERT_EQ(result, expected);

    // in = 0s, load = 1s
    r16.Update(in16_0s, load_1);
    result = r16.Out();
    expected = 0b0000'0000'0000'0000u;
    ASSERT_EQ(result, expected);
}