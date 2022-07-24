#include <gtest/gtest.h>

extern "C" 
{
#include "../src/logic_gates.h"
#include "../src/bits.h"
}

class LogicGatesTest : public ::testing::Test {
    protected:
        bit1_u a = { .value = 0 };
        bit1_u b = { .value = 0 };

        bit1_u res_bit1 = { .value = 0 };
        bit2_u res_bit2 = { .value = 0 };
        bit4_u res_bit4 = { .value = 0 };
        byte1_u res_byte1 = { .value = 0 };
        byte2_u res_byte2 = { .value = 0 };

        bit1_u sel = { .value = 0 };
        bit2_u sel2 = { .value = 0 };
        bit3_u sel3 = { .value = 0 };

        byte1_u a8 = { .value = 0 };

        byte2_u a16 = { .value = 0 };
        byte2_u b16 = { .value = 65535 };
        byte2_u c16 = { .value = 65280 };
        byte2_u d16 = { .value = 255 };
        byte2_u e16 = { .value = 61440 };
        byte2_u f16 = { .value = 3840 };
        byte2_u g16 = { .value = 240 };
        byte2_u h16 = { .value = 15 };
};

TEST_F(LogicGatesTest, Nand) {
    // a=0, b=0
    Nand(&a, &b, &res_bit1);
    ASSERT_TRUE(res_bit1.value);

    // a=1, b=0
    a.value = 1;
    Nand(&a, &b, &res_bit1);
    ASSERT_TRUE(res_bit1.value);

    // a=1, b=1
    b.value = 1;
    Nand(&a, &b, &res_bit1);
    ASSERT_FALSE(res_bit1.value);

    // a=0, b=1
    a.value = 0;
    Nand(&a, &b, &res_bit1);
    ASSERT_TRUE(res_bit1.value);
}


TEST_F(LogicGatesTest, Not) {
    // a=0
    Not(&a, &res_bit1);
    ASSERT_TRUE(res_bit1.value);

    // a=1
    a.value = 1;
    Not(&a, &res_bit1);
    ASSERT_FALSE(res_bit1.value);
}

TEST_F(LogicGatesTest, And) {
    // a=0, b=0
    And(&a, &b, &res_bit1);
    ASSERT_FALSE(res_bit1.value);

    // a=1, b=0
    a.value = 1;
    And(&a, &b, &res_bit1);
    ASSERT_FALSE(res_bit1.value);

    // a=1, b=1
    b.value = 1;
    And(&a, &b, &res_bit1);
    ASSERT_TRUE(res_bit1.value);

    // a=0, b=1
    a.value = 0;
    And(&a, &b, &res_bit1);
    ASSERT_FALSE(res_bit1.value);
}

TEST_F(LogicGatesTest, Or) {
    // a=0, b=0
    Or(&a, &b, &res_bit1);
    ASSERT_FALSE(res_bit1.value);

    // a=1, b=0
    a.value = 1;
    Or(&a, &b, &res_bit1);
    ASSERT_TRUE(res_bit1.value);

    // a=1, b=1
    b.value = 1;
    Or(&a, &b, &res_bit1);
    ASSERT_TRUE(res_bit1.value);

    // a=0, b=1
    a.value = 0;
    Or(&a, &b, &res_bit1);
    ASSERT_TRUE(res_bit1.value);
}

TEST_F(LogicGatesTest, Xor) {
    // a=0, b=0
    Xor(&a, &b, &res_bit1);
    ASSERT_FALSE(res_bit1.value);

    // a=1, b=0
    a.value = 1;
    Xor(&a, &b, &res_bit1);
    ASSERT_TRUE(res_bit1.value);

    // a=1, b=1
    b.value = 1;
    Xor(&a, &b, &res_bit1);
    ASSERT_FALSE(res_bit1.value);

    // a=0, b=1
    a.value = 0;
    Xor(&a, &b, &res_bit1);
    ASSERT_TRUE(res_bit1.value);
}

TEST_F(LogicGatesTest, Mux) {
    // a=0, b=0, sel=0
    Mux(&a, &b, &sel, &res_bit1);
    ASSERT_FALSE(res_bit1.value);
    
    // a=0, b=0, sel=1
    sel.value = 1;
    Mux(&a, &b, &sel, &res_bit1);
    ASSERT_FALSE(res_bit1.value);

    // a=1, b=0, sel=1
    a.value = 1;
    Mux(&a, &b, &sel, &res_bit1);
    ASSERT_FALSE(res_bit1.value);

    // a=1, b=0, sel=0
    sel.value = 0;
    Mux(&a, &b, &sel, &res_bit1);
    ASSERT_TRUE(res_bit1.value);

    // a=1, b=1, sel=0
    b.value = 1;
    Mux(&a, &b, &sel, &res_bit1);
    ASSERT_TRUE(res_bit1.value);

    // a=1, b=1, sel=1
    sel.value = 1;
    Mux(&a, &b, &sel, &res_bit1);
    ASSERT_TRUE(res_bit1.value);

    // a=0, b=1, sel=1
    a.value = 0;
    Mux(&a, &b, &sel, &res_bit1);
    ASSERT_TRUE(res_bit1.value);

    // a=0, b=1, sel=0
    sel.value = 0;
    Mux(&a, &b, &sel, &res_bit1);
    ASSERT_FALSE(res_bit1.value);
}

TEST_F(LogicGatesTest, DMux) {
    // a=0, sel=0
    DMux(&a, &sel, &res_bit2);
    ASSERT_FALSE(res_bit2.bit2_s.val0);
    ASSERT_FALSE(res_bit2.bit2_s.val1);
    
    // a=0, sel=1
    sel.value = 1;
    DMux(&a, &sel, &res_bit2);
    ASSERT_FALSE(res_bit2.bit2_s.val0);
    ASSERT_FALSE(res_bit2.bit2_s.val1);

    // a=1, sel=1
    a.value = 1;
    DMux(&a, &sel, &res_bit2);
    ASSERT_FALSE(res_bit2.bit2_s.val0);
    ASSERT_TRUE(res_bit2.bit2_s.val1);

    // a=1, sel=0
    sel.value = 0;
    DMux(&a, &sel, &res_bit2);
    ASSERT_TRUE(res_bit2.bit2_s.val0);
    ASSERT_FALSE(res_bit2.bit2_s.val1);
}

TEST_F(LogicGatesTest, AndMuxOr) {
    // a=1, b=0, sel=1
    sel.value = 1;
    a.value = 1;
    AndMuxOr(&a, &b, &sel, &res_bit1);
    union bit1_u expected;
    Or(&a, &b, &expected);
    ASSERT_EQ(res_bit1.value, expected.value);

    // a=1, b=0, sel=0
    sel.value = 0;
    AndMuxOr(&a, &b, &sel, &res_bit1);
    And(&a, &b, &expected);
    ASSERT_EQ(res_bit1.value, expected.value);
}

TEST_F(LogicGatesTest, Not16) {
    Not16(&a16, &res_byte2);
    ASSERT_EQ(res_byte2.value, b16.value);
}

TEST_F(LogicGatesTest, And16) {
    // a16=0000'0000'0000'0000
    // b16=0000'0000'0000'0000
    b16.value = 0;
    And16(&a16, &b16, &res_byte2);
    ASSERT_FALSE(res_byte2.value);

    // a16=1111'1111'1111'1111
    // b16=0000'0000'0000'0000
    a16.value = 65535;
    And16(&a16, &b16, &res_byte2);
    ASSERT_FALSE(res_byte2.value);

    // a16=1111'1111'1111'1111
    // b16=1111'1111'1111'1111
    b16.value = 65535;
    And16(&a16, &b16, &res_byte2);
    ASSERT_EQ(res_byte2.value, 65535);

    // a16=0000'0000'0000'0000
    // b16=1111'1111'1111'1111
    a16.value = 0;
    And16(&a16, &b16, &res_byte2);
    ASSERT_FALSE(res_byte2.value);
}

TEST_F(LogicGatesTest, Or16) {
    // a16=0000'0000'0000'0000
    // b16=0000'0000'0000'0000
    b16.value = 0;
    Or16(&a16, &b16, &res_byte2);
    ASSERT_FALSE(res_byte2.value);

    // a16=1111'1111'1111'1111
    // b16=0000'0000'0000'0000
    a16.value = 65535;
    Or16(&a16, &b16, &res_byte2);
    ASSERT_EQ(res_byte2.value, 65535);

    // a16=1111'1111'1111'1111
    // b16=1111'1111'1111'1111
    b16.value = 65535;
    Or16(&a16, &b16, &res_byte2);
    ASSERT_EQ(res_byte2.value, 65535);

    // a16=0000'0000'0000'0000
    // b16=1111'1111'1111'1111
    a16.value = 0;
    Or16(&a16, &b16, &res_byte2);
    ASSERT_EQ(res_byte2.value, 65535);
}

TEST_F(LogicGatesTest, Mux16) {
    // a16=1111'1111'1111'1111
    // b16=0000'0000'0000'0000
    // sel=0
    b16.value = 0;
    a16.value = 65535;
    Mux16(&a16, &b16, &sel, &res_byte2);
    ASSERT_EQ(res_byte2.value, a16.value);

    // a16=1111'1111'1111'1111
    // b16=0000'0000'0000'0000
    // sel=1
    sel.value = 1;
    Mux16(&a16, &b16, &sel, &res_byte2);
    ASSERT_EQ(res_byte2.value, b16.value);
}

TEST_F(LogicGatesTest, Or8Way) {
    // a8=0000'0000
    Or8Way(&a8, &res_byte1);
    ASSERT_FALSE(res_byte1.value);

    a8.byte1_s.val2 = 1;
    Or8Way(&a8, &res_byte1);
    ASSERT_TRUE(res_byte1.value);
}

TEST_F(LogicGatesTest, Mux4Way16) {
    // a16=0000'0000'0000'0000
    // b16=1111'1111'1111'1111
    // c16=1111'1111'0000'0000
    // d16=0000'0000'1111'1111

    // sel2=00
    Mux4Way16(&a16, &b16, &c16, &d16, &sel2, &res_byte2);
    ASSERT_EQ(res_byte2.value, a16.value);

    // sel2=01
    sel2.bit2_s.val0 = 1;
    Mux4Way16(&a16, &b16, &c16, &d16, &sel2, &res_byte2); 
    ASSERT_EQ(res_byte2.value, b16.value);

    // sel2=10
    sel2.bit2_s.val0 = 0;
    sel2.bit2_s.val1 = 1;
    Mux4Way16(&a16, &b16, &c16, &d16, &sel2, &res_byte2); 
    ASSERT_EQ(res_byte2.value, c16.value);
    
    // sel2=11
    sel2.bit2_s.val0 = 1;
    Mux4Way16(&a16, &b16, &c16, &d16, &sel2, &res_byte2); 
    ASSERT_EQ(res_byte2.value, d16.value);
}

TEST_F(LogicGatesTest, Mux8Way16) {
    // a16=0000'0000'0000'0000
    // b16=1111'1111'1111'1111
    // c16=1111'1111'0000'0000
    // d16=0000'0000'1111'1111
    // e16=1111'0000'0000'0000
    // f16=0000'1111'0000'0000
    // g16=0000'0000'1111'0000
    // h16=0000'0000'0000'1111

    // sel3=000
    Mux8Way16(&a16, &b16, &c16, &d16, &e16, &f16, &g16, &h16, &sel3, &res_byte2);
    ASSERT_EQ(res_byte2.value, a16.value);

    // sel3=001
    sel3.bit3_s.val0 = 1;
    Mux8Way16(&a16, &b16, &c16, &d16, &e16, &f16, &g16, &h16, &sel3, &res_byte2); 
    ASSERT_EQ(res_byte2.value, b16.value);

    // sel3=010
    sel3.bit3_s.val0 = 0;
    sel3.bit3_s.val1 = 1;
    Mux8Way16(&a16, &b16, &c16, &d16, &e16, &f16, &g16, &h16, &sel3, &res_byte2); 
    ASSERT_EQ(res_byte2.value, c16.value);

    // sel3=011
    sel3.bit3_s.val0 = 1;
    Mux8Way16(&a16, &b16, &c16, &d16, &e16, &f16, &g16, &h16, &sel3, &res_byte2); 
    ASSERT_EQ(res_byte2.value, d16.value);

    // sel3=100
    sel3.bit3_s.val2 = 1;
    sel3.bit3_s.val1 = 0;
    sel3.bit3_s.val0 = 0;
    Mux8Way16(&a16, &b16, &c16, &d16, &e16, &f16, &g16, &h16, &sel3, &res_byte2); 
    ASSERT_EQ(res_byte2.value, e16.value);

    // sel3=101
    sel3.bit3_s.val0 = 1;
    Mux8Way16(&a16, &b16, &c16, &d16, &e16, &f16, &g16, &h16, &sel3, &res_byte2); 
    ASSERT_EQ(res_byte2.value, f16.value);

    // sel3=110
    sel3.bit3_s.val1 = 1;
    sel3.bit3_s.val0 = 0;
    Mux8Way16(&a16, &b16, &c16, &d16, &e16, &f16, &g16, &h16, &sel3, &res_byte2); 
    ASSERT_EQ(res_byte2.value, g16.value);

    // sel3=111
    sel3.bit3_s.val0 = 1;
    Mux8Way16(&a16, &b16, &c16, &d16, &e16, &f16, &g16, &h16, &sel3, &res_byte2); 
    ASSERT_EQ(res_byte2.value, h16.value);
}

TEST_F(LogicGatesTest, DMux4Way) {
    // a=1, sel2=00
    a.value = 1;;
    DMux4Way(&a, &sel2, &res_bit4); 
    bit4_u expected = { .value = 1 };
    ASSERT_EQ(res_bit4.value, expected.value);

    // a=1, sel=01
    sel2.bit2_s.val0 = 1;
    DMux4Way(&a, &sel2, &res_bit4); 
    expected.value = 2;
    ASSERT_EQ(res_bit4.value, expected.value);

    // a=1, sel=10
    sel2.bit2_s.val1 = 1;
    sel2.bit2_s.val0 = 0;
    DMux4Way(&a, &sel2, &res_bit4); 
    expected.value = 4;
    ASSERT_EQ(res_bit4.value, expected.value);

    // a=1, sel=11
    sel2.bit2_s.val0 = 1;
    DMux4Way(&a, &sel2, &res_bit4); 
    expected.value = 8;
    ASSERT_EQ(res_bit4.value, expected.value);
}

TEST_F(LogicGatesTest, DMux8Way) {
    // a=1, sel3=000
    a.value = 1;
    DMux8Way(&a, &sel3, &res_byte1); 
    byte1_u expected = { .value = 1 };
    ASSERT_EQ(res_byte1.value, expected.value);

    // a=1, sel3=001
    sel3.bit3_s.val0 = 1;
    DMux8Way(&a, &sel3, &res_byte1); 
    expected.value = 2;
    ASSERT_EQ(res_byte1.value, expected.value);

    // a=1, sel=010
    sel3.bit3_s.val1 = 1;
    sel3.bit3_s.val0 = 0;
    DMux8Way(&a, &sel3, &res_byte1); 
    expected.value = 4;
    ASSERT_EQ(res_byte1.value, expected.value);

    // a=1, sel=011
    sel3.bit3_s.val0 = 1;
    DMux8Way(&a, &sel3, &res_byte1); 
    expected.value = 8;
    ASSERT_EQ(res_byte1.value, expected.value);

    // a=1, sel=100
    sel3.bit3_s.val2 = 1;
    sel3.bit3_s.val1 = 0;
    sel3.bit3_s.val0 = 0;
    DMux8Way(&a, &sel3, &res_byte1); 
    expected.value = 16;
    ASSERT_EQ(res_byte1.value, expected.value);

    // a=1, sel=101
    sel3.bit3_s.val0 = 1;
    DMux8Way(&a, &sel3, &res_byte1); 
    expected.value = 32;
    ASSERT_EQ(res_byte1.value, expected.value);

    // a=1, sel=110
    sel3.bit3_s.val1 = 1;
    sel3.bit3_s.val0 = 0;
    DMux8Way(&a, &sel3, &res_byte1); 
    expected.value = 64;
    ASSERT_EQ(res_byte1.value, expected.value);

    // a=1, sel=111
    sel3.bit3_s.val0 = 1;
    DMux8Way(&a, &sel3, &res_byte1); 
    expected.value = 128;
    ASSERT_EQ(res_byte1.value, expected.value);
}


