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

        RAM8 ram8 = RAM8();
        RAM64 ram64 = RAM64();
        RAM512 ram512 = RAM512();
        RAM4k ram4k = RAM4k();
        RAM16k ram16k = RAM16k();
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

TEST_F(MemoryTest, RAM8_test) {
    // initial parameter values
    byte2 result { ram8.Read(0b000u) };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);

    result = ram8.Read(0b001u);
    ASSERT_EQ(result, expected);

    result = ram8.Read(0b010u);
    ASSERT_EQ(result, expected);

    result = ram8.Read(0b011u);
    ASSERT_EQ(result, expected);

    result = ram8.Read(0b100u);
    ASSERT_EQ(result, expected);

    result = ram8.Read(0b101u);
    ASSERT_EQ(result, expected);

    result = ram8.Read(0b110u);
    ASSERT_EQ(result, expected);

    result = ram8.Read(0b111u);
    ASSERT_EQ(result, expected);

    bit3 address { 0b100u };
    ram8.Write(address, in16_1s, load_1);

    result = ram8.Read(0b000u);
    ASSERT_EQ(result, expected);

    result = ram8.Read(0b001u);
    ASSERT_EQ(result, expected);

    result = ram8.Read(0b010u);
    ASSERT_EQ(result, expected);

    result = ram8.Read(0b011u);
    ASSERT_EQ(result, expected);

    result = ram8.Read(0b101u);
    ASSERT_EQ(result, expected);

    result = ram8.Read(0b110u);
    ASSERT_EQ(result, expected);

    result = ram8.Read(0b111u);
    ASSERT_EQ(result, expected);

    expected = 0b1111'1111'1111'1111u;
    result = ram8.Read(0b100u);
    ASSERT_EQ(result, expected);
}

TEST_F(MemoryTest, RAM64_test) {
    // initial parameter values
    byte2 result { ram64.Read(0b000'000u) };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);

    result = ram64.Read(0b001'000u);
    ASSERT_EQ(result, expected);

    result = ram64.Read(0b010'000u);
    ASSERT_EQ(result, expected);

    result = ram64.Read(0b011'000u);
    ASSERT_EQ(result, expected);

    result = ram64.Read(0b100'000u);
    ASSERT_EQ(result, expected);

    result = ram64.Read(0b101'000u);
    ASSERT_EQ(result, expected);

    result = ram64.Read(0b110'000u);
    ASSERT_EQ(result, expected);

    result = ram64.Read(0b111'000u);
    ASSERT_EQ(result, expected);

    bit6 address { 0b100'000u };
    ram64.Write(address, in16_1s, load_1);

    result = ram64.Read(0b000'000u);
    ASSERT_EQ(result, expected);

    result = ram64.Read(0b001'000u);
    ASSERT_EQ(result, expected);

    result = ram64.Read(0b010'000u);
    ASSERT_EQ(result, expected);

    result = ram64.Read(0b011'000u);
    ASSERT_EQ(result, expected);

    result = ram64.Read(0b101'000u);
    ASSERT_EQ(result, expected);

    result = ram64.Read(0b110'000u);
    ASSERT_EQ(result, expected);

    result = ram64.Read(0b111'000u);
    ASSERT_EQ(result, expected);

    expected = 0b1111'1111'1111'1111u;
    result = ram64.Read(0b100'000u);
    ASSERT_EQ(result, expected);
}

TEST_F(MemoryTest, RAM512_test) {
    // initial parameter values
    byte2 result { ram512.Read(0b000'000'000u) };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);

    result = ram512.Read(0b001'000'000u);
    ASSERT_EQ(result, expected);

    result = ram512.Read(0b010'000'000u);
    ASSERT_EQ(result, expected);

    result = ram512.Read(0b011'000'000u);
    ASSERT_EQ(result, expected);

    result = ram512.Read(0b100'000'000u);
    ASSERT_EQ(result, expected);

    result = ram512.Read(0b101'000'000u);
    ASSERT_EQ(result, expected);

    result = ram512.Read(0b110'000'000u);
    ASSERT_EQ(result, expected);

    result = ram512.Read(0b111'000'000u);
    ASSERT_EQ(result, expected);

    bit9 address { 0b100'000'000u };
    ram512.Write(address, in16_1s, load_1);

    result = ram512.Read(0b000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram512.Read(0b001'000'000u);
    ASSERT_EQ(result, expected);

    result = ram512.Read(0b010'000'000u);
    ASSERT_EQ(result, expected);

    result = ram512.Read(0b011'000'000u);
    ASSERT_EQ(result, expected);

    result = ram512.Read(0b101'000'000u);
    ASSERT_EQ(result, expected);

    result = ram512.Read(0b110'000'000u);
    ASSERT_EQ(result, expected);

    result = ram512.Read(0b111'000'000u);
    ASSERT_EQ(result, expected);

    expected = 0b1111'1111'1111'1111u;
    result = ram512.Read(0b100'000'000u);
    ASSERT_EQ(result, expected);
}

TEST_F(MemoryTest, RAM4k_test) {
    // initial parameter values
    byte2 result { ram4k.Read(0b000'000'000'000u) };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);

    result = ram4k.Read(0b001'000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram4k.Read(0b010'000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram4k.Read(0b011'000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram4k.Read(0b100'000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram4k.Read(0b101'000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram4k.Read(0b110'000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram4k.Read(0b111'000'000'000u);
    ASSERT_EQ(result, expected);

    bit12 address { 0b100'000'000'000u };
    ram4k.Write(address, in16_1s, load_1);

    result = ram4k.Read(0b000'000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram4k.Read(0b001'000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram4k.Read(0b010'000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram4k.Read(0b011'000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram4k.Read(0b101'000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram4k.Read(0b110'000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram4k.Read(0b111'000'000'000u);
    ASSERT_EQ(result, expected);

    expected = 0b1111'1111'1111'1111u;
    result = ram4k.Read(0b100'000'000'000u);
    ASSERT_EQ(result, expected);
}

TEST_F(MemoryTest, RAM16k_test) {
    // initial parameter values
    byte2 result { ram16k.Read(0b0000'000'000'000'000u) };
    byte2 expected { 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);

    result = ram16k.Read(0b0001'000'000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram16k.Read(0b0010'000'000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram16k.Read(0b0011'000'000'000'000u);
    ASSERT_EQ(result, expected);

    byte2 address { 0b0010'000'000'000'000u };
    ram16k.Write(address, in16_1s, load_1);

    result = ram16k.Read(0b0000'000'000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram16k.Read(0b0001'000'000'000'000u);
    ASSERT_EQ(result, expected);

    result = ram16k.Read(0b0011'000'000'000'000u);
    ASSERT_EQ(result, expected);

    expected = 0b1111'1111'1111'1111u;
    result = ram16k.Read(0b0010'000'000'000'000u);
    ASSERT_EQ(result, expected);
}
