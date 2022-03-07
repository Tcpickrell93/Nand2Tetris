#include "../src/arithmetic_chips.h"

#include <gtest/gtest.h>


class ArithmeticChipsTest: public ::testing::Test {
    protected:
        bit a{ 0b0u };
        bit b{ 0b0u };
        bit c{ 0b0u };

        bit za{ 0b0u };
        bit na{ 0b0u };
        bit zb{ 0b0u };
        bit nb{ 0b0u };
        bit f{ 0b0u };
        bit no{ 0b0u };
        bit zr{ 0b0u };
        bit ng{ 0b0u };

        byte2 a16{ 0b0000'0000'1111'0000u };
        byte2 b16{ 0b0000'0000'0000'1111u };
};

TEST_F(ArithmeticChipsTest, HalfAdder_in_00) {
    // a=0, b=0
    bit2 result{ HalfAdder(a, b) };
    bit2 expected{ 0b00u };
    ASSERT_EQ(result, expected);
}

TEST_F(ArithmeticChipsTest, HalfAdder_in_10) {
    // a=1, b=0
    a.set();
    bit2 result{ HalfAdder(a, b) };
    bit2 expected{ 0b01u };
    ASSERT_EQ(result, expected);
}

TEST_F(ArithmeticChipsTest, HalfAdder_in_01) {
    // a=0, b=1
    b.set();
    bit2 result{ HalfAdder(a, b) };
    bit2 expected{ 0b01u };
    ASSERT_EQ(result, expected);
}

TEST_F(ArithmeticChipsTest, HalfAdder_in_11) {
    // a=1, b=1
    a.set();
    b.set();
    bit2 result{ HalfAdder(a, b) };
    bit2 expected{ 0b10u };
    ASSERT_EQ(result, expected);
}

TEST_F(ArithmeticChipsTest, FullAdder_in_000) {
    // a=0, b=0, c=0
    bit2 result{ FullAdder(a, b, c) };
    bit2 expected{ 0b00u };
    ASSERT_EQ(result, expected);
}

TEST_F(ArithmeticChipsTest, FullAdder_in_100) {
    // a=1, b=0, c=0
    a.set();
    bit2 result{ FullAdder(a, b, c) };
    bit2 expected{ 0b01u };
    ASSERT_EQ(result, expected);
}

TEST_F(ArithmeticChipsTest, FullAdder_in_010) {
    // a=0, b=1, c=0
    b.set();
    bit2 result{ FullAdder(a, b, c) };
    bit2 expected{ 0b01u };
    ASSERT_EQ(result, expected);
}

TEST_F(ArithmeticChipsTest, FullAdder_in_001) {
    // a=0, b=0, c=1
    c.set();
    bit2 result{ FullAdder(a, b, c) };
    bit2 expected{ 0b01u };
    ASSERT_EQ(result, expected);
}

TEST_F(ArithmeticChipsTest, FullAdder_in_110) {
    // a=1, b=1, c=0
    a.set();
    b.set();
    bit2 result{ FullAdder(a, b, c) };
    bit2 expected{ 0b10u };
    ASSERT_EQ(result, expected);
}

TEST_F(ArithmeticChipsTest, FullAdder_in_101) {
    // a=1, b=0, c=1
    a.set();
    c.set();
    bit2 result{ FullAdder(a, b, c) };
    bit2 expected{ 0b10u };
    ASSERT_EQ(result, expected);
}

TEST_F(ArithmeticChipsTest, FullAdder_in_011) {
    // a=0, b=1, c=1
    b.set();
    c.set();
    bit2 result{ FullAdder(a, b, c) };
    bit2 expected{ 0b10u };
    ASSERT_EQ(result, expected);
}

TEST_F(ArithmeticChipsTest, FullAdder_in_111) {
    // a=1, b=1, c=1
    a.set();
    b.set();
    c.set();
    bit2 result{ FullAdder(a, b, c) };
    bit2 expected{ 0b11u };
    ASSERT_EQ(result, expected);
}

TEST_F(ArithmeticChipsTest, Add16) {
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    byte2 result{ Add16(a16, b16) };
    byte2 expected{ 0b0000'0000'1111'1111u };
    ASSERT_EQ(result, expected);
}

TEST_F(ArithmeticChipsTest, Inc16) {
    // a16=0000'0000'1111'0000
    byte2 result{ Inc16(a16) };
    byte2 expected{ 0b0000'0000'1111'0001u };
    ASSERT_EQ(result, expected);
}

TEST_F(ArithmeticChipsTest, ALU_out_0) {
    // output = 0
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=1, na=0, zb=1, nb=0, f=1, no=0
    za.set();
    zb.set();
    f.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 1);
    ASSERT_EQ(ng[0], 0);
}
 
TEST_F(ArithmeticChipsTest, ALU_out_1) {
    // output = 1
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=1, na=1, zb=1, nb=1, f=1, no=1
    za.set();
    na.set();
    zb.set();
    nb.set();
    f.set();
    no.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b0000'0000'0000'0001u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 0);
    ASSERT_EQ(ng[0], 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_neg_1) {
    // output = -1
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=1, na=1, zb=1, nb=0, f=1, no=0
    za.set();
    na.set();
    zb.set();
    f.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b1111'1111'1111'1111u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 0);
    ASSERT_EQ(ng[0], 1);
}

TEST_F(ArithmeticChipsTest, ALU_out_a) {
    // output = a
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=0, zb=1, nb=1, f=0, no=0
    zb.set();
    nb.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b0000'0000'1111'0000u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 0);
    ASSERT_EQ(ng[0], 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_b) {
    // output = b
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=1, na=1, zb=0, nb=0, f=0, no=0
    za.set();
    na.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b0000'0000'0000'1111u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 0);
    ASSERT_EQ(ng[0], 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_not_a) {
    // output = !a
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=0, zb=1, nb=1, f=0, no=1
    zb.set();
    nb.set();
    no.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b1111'1111'0000'1111u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 0);
    ASSERT_EQ(ng[0], 1);
}

TEST_F(ArithmeticChipsTest, ALU_out_not_b) {
    // output = !b
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=1, na=1, zb=0, nb=0, f=0, no=1
    za.set();
    na.set();
    no.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b1111'1111'1111'0000u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 0);
    ASSERT_EQ(ng[0], 1);
}

TEST_F(ArithmeticChipsTest, ALU_out_neg_a) {
    // output = -a
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=0, zb=1, nb=1, f=1, no=1
    zb.set();
    nb.set();
    f.set();
    no.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b1111'1111'0001'0000u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 0);
    ASSERT_EQ(ng[0], 1);
}

TEST_F(ArithmeticChipsTest, ALU_out_neg_b) {
    // output = -b
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=1, na=1, zb=0, nb=0, f=1, no=1
    za.set();
    na.set();
    f.set();
    no.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b1111'1111'1111'0001u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 0);
    ASSERT_EQ(ng[0], 1);
}

TEST_F(ArithmeticChipsTest, ALU_out_a_plus_1) {
    // output = a+1
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=1, zb=1, nb=1, f=1, no=1
    na.set();
    zb.set();
    nb.set();
    f.set();
    no.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b0000'0000'1111'0001u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 0);
    ASSERT_EQ(ng[0], 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_b_plus_1) {
    // output = b+1
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=1, na=1, zb=0, nb=1, f=1, no=1
    za.set();
    na.set();
    nb.set();
    f.set();
    no.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b0000'0000'0001'0000u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 0);
    ASSERT_EQ(ng[0], 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_a_minus_1) {
    // output = a-1
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=0, zb=1, nb=1, f=1, no=0
    zb.set();
    nb.set();
    f.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b0000'0000'1110'1111u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 0);
    ASSERT_EQ(ng[0], 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_b_minus_1) {
    // output = b-1
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=1, na=1, zb=0, nb=0, f=1, no=0
    za.set();
    na.set();
    f.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b0000'0000'0000'1110u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 0);
    ASSERT_EQ(ng[0], 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_a_plus_b) {
    // output = a+b
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=0, zb=0, nb=0, f=1, no=0
    f.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b0000'0000'1111'1111u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 0);
    ASSERT_EQ(ng[0], 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_a_minus_b) {
    // output = a-b
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=1, zb=0, nb=0, f=1, no=1
    na.set();
    f.set();
    no.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b0000'0000'1110'0001u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 0);
    ASSERT_EQ(ng[0], 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_b_minus_a) {
    // output = b-a
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=0, zb=0, nb=1, f=1, no=1
    nb.set();
    f.set();
    no.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b1111'1111'0001'1111u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 0);
    ASSERT_EQ(ng[0], 1);
}

TEST_F(ArithmeticChipsTest, ALU_out_a_and_b) {
    // output = a&b
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=0, zb=0, nb=0, f=0, no=0
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b0000'0000'0000'0000u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 1);
    ASSERT_EQ(ng[0], 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_a_or_b) {
    // output = a|b
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=1, zb=0, nb=1, f=0, no=1
    na.set();
    nb.set();
    no.set();
    byte2 result{ ALU(a16, b16, za, na, zb, nb, f, no, zr, ng) };
    byte2 expected{ 0b0000'0000'1111'1111u };
    ASSERT_EQ(result, expected);
    ASSERT_EQ(zr[0], 0);
    ASSERT_EQ(ng[0], 0);
}
