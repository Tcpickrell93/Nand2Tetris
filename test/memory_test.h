#include "../src/memory.h"

#include <gtest/gtest.h>
#include <iostream>


class MemoryTest: public ::testing::Test {
    protected:
        DataFlipFLop dff = DataFlipFLop();
        RegisterBit rb = RegisterBit();

        const bit in_1 = { 0b1u };
        const bit in_0 = { 0b0u };
        
        const bit load_1 = { 0b1u };
        const bit load_0 = { 0b0u };
};

TEST_F(MemoryTest, DataFlipFLop_test) {
    // initial parameter values
    bit result{ dff.Out() };
    bit expected{ 0b0u };
    ASSERT_EQ(result, expected);

    // update bit
    dff.Update(in_1);
    result = dff.Out();
    expected = 0b1u;
    ASSERT_EQ(result, expected);
}

TEST_F(MemoryTest, RegisterBit_test) {
    // initial parameter values
    bit result{ rb.Out() };
    bit expected{ 0b0u };
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

/*
TEST_F(MemoryTest, Register16) {
    // in=0000'0000'0000'0000, load=0
    //std::cout << "a: " << a << ", load: " << load << ", prev_out: " << prev_out << std::endl; 
    byte2 result{ Register16(in16, load, prev_out16, prev_in16) };
    byte2 expected{ 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
    
    // change in to 1
    // output should not change - load not active
    a.set();
    //std::cout << "a: " << a << ", load: " << load << ", prev_out: " << prev_out << std::endl; 
    result = RegisterBit(in16, load, prev_out16, prev_in16);
    byte2 expected{ 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);

    // change load to 1
    // output should have changed - looks at prev load
    load.set();
    //std::cout << "a: " << a << ", load: " << load << ", prev_out: " << prev_out << std::endl; 
    result = RegisterBit(in16, load, prev_out16, prev_in16);
    byte2 expected{ 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
    
    // don't change anything
    // output should be 1 since load and prev in were both 1
    //std::cout << "a: " << a << ", load: " << load << ", prev_out: " << prev_out << std::endl; 
    result = RegisterBit(in16, load, prev_out16, prev_in16);
    byte2 expected{ 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);

    // don't change anything
    // should maintain 1
    //std::cout << "a: " << a << ", load: " << load << ", prev_out: " << prev_out << std::endl; 
    result = RegisterBit(in16, load, prev_out16, prev_in16);
    byte2 expected{ 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
}
*/