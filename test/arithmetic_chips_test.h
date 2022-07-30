#include <gtest/gtest.h>

extern "C"
{
#include "../src/arithmetic_chips.h"
#include "../src/bits.h"
}

class ArithmeticChipsTest: public ::testing::Test {
    protected:
        union bit1_u a = { .value = 0 };
        union bit1_u b = { .value = 0 };
        union bit1_u c = { .value = 0 };

        union bit1_u za = { .value = 0 };
        union bit1_u na = { .value = 0 };
        union bit1_u zb = { .value = 0 };
        union bit1_u nb = { .value = 0 };
        union bit1_u f = { .value = 0 };
        union bit1_u no = { .value = 0 };
        union bit1_u zr = { .value = 0 };
        union bit1_u ng = { .value = 0 };

        union byte2_u a16 = { .value = 240 };
        union byte2_u b16 = { .value = 15 };

        union bit1_u res_bit1 = { .value = 0 };
        union bit2_u res_bit2 = { .value = 0 };
        union bit4_u res_bit4 = { .value = 0 };
        union byte1_u res_byte1 = { .value = 0 };
        union byte2_u res_byte2 = { .value = 0 };
};

TEST_F(ArithmeticChipsTest, HalfAdder_in_00) {
    // a=0, b=0
    HalfAdder(&a, &b, &res_bit2);
    union bit2_u expected = { .value = 0 };
    ASSERT_EQ(res_bit2.value, expected.value);
}

TEST_F(ArithmeticChipsTest, HalfAdder_in_10) {
    // a=1, b=0
    a.value = 1;
    HalfAdder(&a, &b, &res_bit2);
    union bit2_u expected = { .value = 1 };
    ASSERT_EQ(res_bit2.value, expected.value);
}

TEST_F(ArithmeticChipsTest, HalfAdder_in_01) {
    // a=0, b=1
    b.value = 1;
    HalfAdder(&a, &b, &res_bit2);
    union bit2_u expected = { .value = 1 };
    ASSERT_EQ(res_bit2.value, expected.value);
}

TEST_F(ArithmeticChipsTest, HalfAdder_in_11) {
    // a=1, b=1
    a.value = 1;
    b.value = 1;
    HalfAdder(&a, &b, &res_bit2);
    union bit2_u expected = { .value = 2 };
    ASSERT_EQ(res_bit2.value, expected.value);
}

TEST_F(ArithmeticChipsTest, FullAdder_in_000) {
    // a=0, b=0, c=0
    FullAdder(&a, &b, &c, &res_bit2);
    union bit2_u expected = { .value = 0 };
    ASSERT_EQ(res_bit2.value, expected.value);
}

TEST_F(ArithmeticChipsTest, FullAdder_in_100) {
    // a=1, b=0, c=0
    a.value = 1;
    FullAdder(&a, &b, &c, &res_bit2);
    union bit2_u expected = { .value = 1 };
    ASSERT_EQ(res_bit2.value, expected.value);
}

TEST_F(ArithmeticChipsTest, FullAdder_in_010) {
    // a=0, b=1, c=0
    b.value = 1;
    FullAdder(&a, &b, &c, &res_bit2);
    union bit2_u expected = { .value = 1 };
    ASSERT_EQ(res_bit2.value, expected.value);
}

TEST_F(ArithmeticChipsTest, FullAdder_in_001) {
    // a=0, b=0, c=1
    c.value = 1;
    FullAdder(&a, &b, &c, &res_bit2);
    union bit2_u expected = { .value = 1 };
    ASSERT_EQ(res_bit2.value, expected.value);
}

TEST_F(ArithmeticChipsTest, FullAdder_in_110) {
    // a=1, b=1, c=0
    a.value = 1;
    b.value = 1;
    FullAdder(&a, &b, &c, &res_bit2);
    union bit2_u expected = { .value = 2 };
    ASSERT_EQ(res_bit2.value, expected.value);
}

TEST_F(ArithmeticChipsTest, FullAdder_in_101) {
    // a=1, b=0, c=1
    a.value = 1;
    c.value = 1;
    FullAdder(&a, &b, &c, &res_bit2);
    union bit2_u expected = { .value = 2 };
    ASSERT_EQ(res_bit2.value, expected.value);
}

TEST_F(ArithmeticChipsTest, FullAdder_in_011) {
    // a=0, b=1, c=1
    b.value = 1;
    c.value = 1;
    FullAdder(&a, &b, &c, &res_bit2);
    union bit2_u expected = { .value = 2 };
    ASSERT_EQ(res_bit2.value, expected.value);
}

TEST_F(ArithmeticChipsTest, FullAdder_in_111) {
    // a=1, b=1, c=1
    a.value = 1;
    b.value = 1;
    c.value = 1;
    FullAdder(&a, &b, &c, &res_bit2);
    union bit2_u expected = { .value = 3 };
    ASSERT_EQ(res_bit2.value, expected.value);
}

TEST_F(ArithmeticChipsTest, Add16) {
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    Add16(&a16, &b16, &res_byte2);
    union byte2_u expected = { .value = 255 };
    ASSERT_EQ(res_byte2.value, expected.value);
}

TEST_F(ArithmeticChipsTest, Inc16) {
    // a16=0000'0000'1111'0000
    Inc16(&a16, &res_byte2);
    union byte2_u expected = { .value = 241 };
    ASSERT_EQ(res_byte2.value, expected.value);
}

TEST_F(ArithmeticChipsTest, ALU_out_0) {
    // output = 0
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=1, na=0, zb=1, nb=0, f=1, no=0
    za.value = 1;
    zb.value = 1;
    f.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 0 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 1);
    ASSERT_EQ(ng.value, 0);
}
 
TEST_F(ArithmeticChipsTest, ALU_out_1) {
    // output = 1
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=1, na=1, zb=1, nb=1, f=1, no=1
    za.value = 1;
    na.value = 1;
    zb.value = 1;
    nb.value = 1;
    f.value = 1;
    no.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 1 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 0);
    ASSERT_EQ(ng.value, 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_neg_1) {
    // output = -1
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=1, na=1, zb=1, nb=0, f=1, no=0
    za.value = 1;
    na.value = 1;
    zb.value = 1;
    f.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 65535 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 0);
    ASSERT_EQ(ng.value, 1);
}

TEST_F(ArithmeticChipsTest, ALU_out_a) {
    // output = a
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=0, zb=1, nb=1, f=0, no=0
    zb.value = 1;
    nb.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 240 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 0);
    ASSERT_EQ(ng.value, 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_b) {
    // output = b
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=1, na=1, zb=0, nb=0, f=0, no=0
    za.value = 1;
    na.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 15 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 0);
    ASSERT_EQ(ng.value, 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_not_a) {
    // output = !a
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=0, zb=1, nb=1, f=0, no=1
    zb.value = 1;
    nb.value = 1;
    no.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 65295 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 0);
    ASSERT_EQ(ng.value, 1);
}

TEST_F(ArithmeticChipsTest, ALU_out_not_b) {
    // output = !b
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=1, na=1, zb=0, nb=0, f=0, no=1
    za.value = 1;
    na.value = 1;
    no.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 65520 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 0);
    ASSERT_EQ(ng.value, 1);
}

TEST_F(ArithmeticChipsTest, ALU_out_neg_a) {
    // output = -a
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=0, zb=1, nb=1, f=1, no=1
    zb.value = 1;
    nb.value = 1;
    f.value = 1;
    no.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 65296 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 0);
    ASSERT_EQ(ng.value, 1);
}

TEST_F(ArithmeticChipsTest, ALU_out_neg_b) {
    // output = -b
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=1, na=1, zb=0, nb=0, f=1, no=1
    za.value = 1;
    na.value = 1;
    f.value = 1;
    no.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 65521 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 0);
    ASSERT_EQ(ng.value, 1);
}

TEST_F(ArithmeticChipsTest, ALU_out_a_plus_1) {
    // output = a+1
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=1, zb=1, nb=1, f=1, no=1
    na.value = 1;
    zb.value = 1;
    nb.value = 1;
    f.value = 1;
    no.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 241 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 0);
    ASSERT_EQ(ng.value, 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_b_plus_1) {
    // output = b+1
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=1, na=1, zb=0, nb=1, f=1, no=1
    za.value = 1;
    na.value = 1;
    nb.value = 1;
    f.value = 1;
    no.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 16 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 0);
    ASSERT_EQ(ng.value, 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_a_minus_1) {
    // output = a-1
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=0, zb=1, nb=1, f=1, no=0
    zb.value = 1;
    nb.value = 1;
    f.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 239 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 0);
    ASSERT_EQ(ng.value, 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_b_minus_1) {
    // output = b-1
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=1, na=1, zb=0, nb=0, f=1, no=0
    za.value = 1;
    na.value = 1;
    f.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 14 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 0);
    ASSERT_EQ(ng.value, 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_a_plus_b) {
    // output = a+b
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=0, zb=0, nb=0, f=1, no=0
    f.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 255 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 0);
    ASSERT_EQ(ng.value, 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_a_minus_b) {
    // output = a-b
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=1, zb=0, nb=0, f=1, no=1
    na.value = 1;
    f.value = 1;
    no.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 225 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 0);
    ASSERT_EQ(ng.value, 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_b_minus_a) {
    // output = b-a
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=0, zb=0, nb=1, f=1, no=1
    nb.value = 1;
    f.value = 1;
    no.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 65311 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 0);
    ASSERT_EQ(ng.value, 1);
}

TEST_F(ArithmeticChipsTest, ALU_out_a_and_b) {
    // output = a&b
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=0, zb=0, nb=0, f=0, no=0
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 0 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 1);
    ASSERT_EQ(ng.value, 0);
}

TEST_F(ArithmeticChipsTest, ALU_out_a_or_b) {
    // output = a|b
    // a16=0000'0000'1111'0000
    // b16=0000'0000'0000'1111
    // za=0, na=1, zb=0, nb=1, f=0, no=1
    na.value = 1;
    nb.value = 1;
    no.value = 1;
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    union byte2_u expected = { .value = 255 };
    ASSERT_EQ(res_byte2.value, expected.value);
    ASSERT_EQ(zr.value, 0);
    ASSERT_EQ(ng.value, 0);
}
