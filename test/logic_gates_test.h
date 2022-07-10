#include "../src/logic_gates.h"

#include <gtest/gtest.h>


class LogicGatesTest : public ::testing::Test {
    protected:
        bit1_u a { 0 };
        bit1_u b { 0 };
        bit1_u sel { 0 };

        bit2_u sel2 { 0 };
        
        bit3_u sel3 { 0 };

        byte1_u a8 { 0 };

        byte2_u a16 { 0 };
        byte2_u b16 { 65535 };
        byte2_u c16 { 65280 };
        byte2_u d16 { 255 };
        byte2_u e16 { 61440 };
        byte2_u f16 { 3840 };
        byte2_u g16 { 240 };
        byte2_u h16 { 15 };
};

TEST_F(LogicGatesTest, Nand) {
    // a=0, b=0
    ASSERT_TRUE(Nand(a, b).value);

    // a=1, b=0
    a.value = 1;
    ASSERT_TRUE(Nand(a, b).value);

    // a=1, b=1
    b.value = 1;
    ASSERT_FALSE(Nand(a, b).value);

    // a=0, b=1
    a.value = 0;
    ASSERT_TRUE(Nand(a, b).value);
}
    
TEST_F(LogicGatesTest, Not) {
    // a=0
    ASSERT_TRUE(Not(a).value);

    // a=1
    a.value = 1;
    ASSERT_FALSE(Not(a).value);
}

TEST_F(LogicGatesTest, And) {
    // a=0, b=0
    ASSERT_FALSE(And(a, b).value);

    // a=1, b=0
    a.value = 1;
    ASSERT_FALSE(And(a, b).value);

    // a=1, b=1
    b.value = 1;
    ASSERT_TRUE(And(a, b).value);

    // a=0, b=1
    a.value = 0;
    ASSERT_FALSE(And(a, b).value);
}

TEST_F(LogicGatesTest, Or) {
    // a=0, b=0
    ASSERT_FALSE(Or(a, b).value);

    // a=1, b=0
    a.value = 1;;
    ASSERT_TRUE(Or(a, b).value);

    // a=1, b=1
    b.value = 1;
    ASSERT_TRUE(Or(a, b).value);

    // a=0, b=1
    a.value = 0;
    ASSERT_TRUE(Or(a, b).value);
}

TEST_F(LogicGatesTest, Xor) {
    // a=0, b=0
    ASSERT_FALSE(Xor(a, b).value);

    // a=1, b=0
    a.value = 1;;
    ASSERT_TRUE(Xor(a, b).value);

    // a=1, b=1
    b.value = 1;
    ASSERT_FALSE(Xor(a, b).value);

    // a=0, b=1
    a.value = 0;
    ASSERT_TRUE(Xor(a, b).value);
}

TEST_F(LogicGatesTest, Mux) {
    // a=0, b=0, sel=0
    ASSERT_FALSE(Mux(a, b, sel).value);
    
    // a=0, b=0, sel=1
    sel.value = 1;
    ASSERT_FALSE(Mux(a, b, sel).value);

    // a=1, b=0, sel=1
    a.value = 1;;
    ASSERT_FALSE(Mux(a, b, sel).value);

    // a=1, b=0, sel=0
    sel.value = 0;
    ASSERT_TRUE(Mux(a, b, sel).value);

    // a=1, b=1, sel=0
    b.value = 1;
    ASSERT_TRUE(Mux(a, b, sel).value);

    // a=1, b=1, sel=1
    sel.value = 1;
    ASSERT_TRUE(Mux(a, b, sel).value);

    // a=0, b=1, sel=1
    a.value = 0;
    ASSERT_TRUE(Mux(a, b, sel).value);

    // a=0, b=1, sel=0
    sel.value = 0;
    ASSERT_FALSE(Mux(a, b, sel).value);
}

TEST_F(LogicGatesTest, DMux) {
    // a=0, sel=0
    bit2_u result{ DMux(a, sel) };
    ASSERT_FALSE(result.bit2_s.val0);
    ASSERT_FALSE(result.bit2_s.val1);
    
    // a=0, sel=1
    sel.value = 1;
    result = DMux(a, sel); 
    ASSERT_FALSE(result.bit2_s.val0);
    ASSERT_FALSE(result.bit2_s.val1);

    // a=1, sel=1
    a.value = 1;;
    result = DMux(a, sel); 
    ASSERT_FALSE(result.bit2_s.val0);
    ASSERT_TRUE(result.bit2_s.val1);

    // a=1, sel=0
    sel.value = 0;
    result = DMux(a, sel); 
    ASSERT_TRUE(result.bit2_s.val0);
    ASSERT_FALSE(result.bit2_s.val1);
}

TEST_F(LogicGatesTest, AndMuxOr) {
    // a=1, b=0, sel=1
    sel.value = 1;
    a.value = 1;;
    ASSERT_EQ(AndMuxOr(a, b, sel).value, Or(a, b).value);

    // a=1, b=0, sel=0
    sel.value = 0;
    ASSERT_EQ(AndMuxOr(a, b, sel).value, And(a, b).value);
}

TEST_F(LogicGatesTest, Not16) {
    byte2_u result{ Not16(a16) };
    ASSERT_EQ(result.value, b16.value);
}

TEST_F(LogicGatesTest, And16) {
    // a16=0000'0000'0000'0000
    // b16=0000'0000'0000'0000
    b16.value = 0;
    byte2_u result{ And16(a16, b16) };
    ASSERT_FALSE(result.value);

    // a16=1111'1111'1111'1111
    // b16=0000'0000'0000'0000
    a16.value = 65535;
    result = And16(a16, b16);
    ASSERT_FALSE(result.value);

    // a16=1111'1111'1111'1111
    // b16=1111'1111'1111'1111
    b16.value = 65535;
    result = And16(a16, b16);
    ASSERT_EQ(result.value, 65535);

    // a16=0000'0000'0000'0000
    // b16=1111'1111'1111'1111
    a16.value = 0;
    result = And16(a16, b16);
    ASSERT_FALSE(result.value);
}

TEST_F(LogicGatesTest, Or16) {
    // a16=0000'0000'0000'0000
    // b16=0000'0000'0000'0000
    b16.value = 0;
    byte2_u result{ Or16(a16, b16) };
    ASSERT_FALSE(result.value);

    // a16=1111'1111'1111'1111
    // b16=0000'0000'0000'0000
    a16.value = 65535;
    result = Or16(a16, b16);
    ASSERT_EQ(result.value, 65535);

    // a16=1111'1111'1111'1111
    // b16=1111'1111'1111'1111
    b16.value = 65535;
    result = Or16(a16, b16);
    ASSERT_EQ(result.value, 65535);

    // a16=0000'0000'0000'0000
    // b16=1111'1111'1111'1111
    a16.value = 0;
    result = Or16(a16, b16);
    ASSERT_EQ(result.value, 65535);
}

TEST_F(LogicGatesTest, Mux16) {
    // a16=1111'1111'1111'1111
    // b16=0000'0000'0000'0000
    // sel=0
    b16.value = 0;
    a16.value = 65535;
    byte2_u result{ Mux16(a16, b16, sel) };
    ASSERT_EQ(result.value, a16.value);

    // a16=1111'1111'1111'1111
    // b16=0000'0000'0000'0000
    // sel=1
    sel.value = 1;
    result = Mux16(a16, b16, sel);
    ASSERT_EQ(result.value, b16.value);
}

TEST_F(LogicGatesTest, Or8Way) {
    // a8=0000'0000
    ASSERT_FALSE(Or8Way(a8).value);

    a8.byte1_s.val2 = 1;
    ASSERT_TRUE(Or8Way(a8).value);
}

TEST_F(LogicGatesTest, Mux4Way16) {
    // a16=0000'0000'0000'0000
    // b16=1111'1111'1111'1111
    // c16=1111'1111'0000'0000
    // d16=0000'0000'1111'1111

    // sel2=00
    byte2_u result{ Mux4Way16(a16, b16, c16, d16, sel2) };
    ASSERT_EQ(result.value, a16.value);

    // sel2=01
    sel2.bit2_s.val0 = 1;
    result = Mux4Way16(a16, b16, c16, d16, sel2); 
    ASSERT_EQ(result.value, b16.value);

    // sel2=10
    sel2.bit2_s.val0 = 0;
    sel2.bit2_s.val1 = 1;
    result = Mux4Way16(a16, b16, c16, d16, sel2); 
    ASSERT_EQ(result.value, c16.value);
    
    // sel2=11
    sel2.bit2_s.val0 = 1;
    result = Mux4Way16(a16, b16, c16, d16, sel2); 
    ASSERT_EQ(result.value, d16.value);
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
    byte2_u result{ Mux8Way16(a16, b16, c16, d16, e16, f16, g16, h16, sel3) };
    ASSERT_EQ(result.value, a16.value);

    // sel3=001
    sel3.bit3_s.val0 = 1;
    result = Mux8Way16(a16, b16, c16, d16, e16, f16, g16, h16, sel3); 
    ASSERT_EQ(result.value, b16.value);

    // sel3=010
    sel3.bit3_s.val0 = 0;
    sel3.bit3_s.val1 = 1;
    result = Mux8Way16(a16, b16, c16, d16, e16, f16, g16, h16, sel3); 
    ASSERT_EQ(result.value, c16.value);

    // sel3=011
    sel3.bit3_s.val0 = 1;
    result = Mux8Way16(a16, b16, c16, d16, e16, f16, g16, h16, sel3); 
    ASSERT_EQ(result.value, d16.value);

    // sel3=100
    sel3.bit3_s.val2 = 1;
    sel3.bit3_s.val1 = 0;
    sel3.bit3_s.val0 = 0;
    result = Mux8Way16(a16, b16, c16, d16, e16, f16, g16, h16, sel3); 
    ASSERT_EQ(result.value, e16.value);

    // sel3=101
    sel3.bit3_s.val0 = 1;
    result = Mux8Way16(a16, b16, c16, d16, e16, f16, g16, h16, sel3); 
    ASSERT_EQ(result.value, f16.value);

    // sel3=110
    sel3.bit3_s.val1 = 1;
    sel3.bit3_s.val0 = 0;
    result = Mux8Way16(a16, b16, c16, d16, e16, f16, g16, h16, sel3); 
    ASSERT_EQ(result.value, g16.value);

    // sel3=111
    sel3.bit3_s.val0 = 1;
    result = Mux8Way16(a16, b16, c16, d16, e16, f16, g16, h16, sel3); 
    ASSERT_EQ(result.value, h16.value);
}

TEST_F(LogicGatesTest, DMux4Way) {
    // a=1, sel2=00
    a.value = 1;;
    bit4_u result{ DMux4Way(a, sel2) }; 
    bit4_u expected{ 1 };
    ASSERT_EQ(result.value, expected.value);

    // a=1, sel=01
    sel2.bit2_s.val0 = 1;
    result = DMux4Way(a, sel2); 
    expected.value = 2;
    ASSERT_EQ(result.value, expected.value);

    // a=1, sel=10
    sel2.bit2_s.val1 = 1;
    sel2.bit2_s.val0 = 0;
    result = DMux4Way(a, sel2); 
    expected.value = 4;
    ASSERT_EQ(result.value, expected.value);

    // a=1, sel=11
    sel2.bit2_s.val0 = 1;
    result = DMux4Way(a, sel2); 
    expected.value = 8;
    ASSERT_EQ(result.value, expected.value);
}

TEST_F(LogicGatesTest, DMux8Way) {
    // a=1, sel3=000
    a.value = 1;;
    byte1_u result{ DMux8Way(a, sel3) }; 
    byte1_u expected{ 1 };
    ASSERT_EQ(result.value, expected.value);

    // a=1, sel3=001
    sel3.bit3_s.val0 = 1;
    result = DMux8Way(a, sel3); 
    expected.value = 2;
    ASSERT_EQ(result.value, expected.value);

    // a=1, sel=010
    sel3.bit3_s.val1 = 1;
    sel3.bit3_s.val0 = 0;
    result = DMux8Way(a, sel3); 
    expected.value = 4;
    ASSERT_EQ(result.value, expected.value);

    // a=1, sel=011
    sel3.bit3_s.val0 = 1;
    result = DMux8Way(a, sel3); 
    expected.value = 8;
    ASSERT_EQ(result.value, expected.value);

    // a=1, sel=100
    sel3.bit3_s.val2 = 1;
    sel3.bit3_s.val1 = 0;
    sel3.bit3_s.val0 = 0;
    result = DMux8Way(a, sel3); 
    expected.value = 16;
    ASSERT_EQ(result.value, expected.value);

    // a=1, sel=101
    sel3.bit3_s.val0 = 1;
    result = DMux8Way(a, sel3); 
    expected.value = 32;
    ASSERT_EQ(result.value, expected.value);

    // a=1, sel=110
    sel3.bit3_s.val1 = 1;
    sel3.bit3_s.val0 = 0;
    result = DMux8Way(a, sel3); 
    expected.value = 64;
    ASSERT_EQ(result.value, expected.value);

    // a=1, sel=111
    sel3.bit3_s.val0 = 1;
    result = DMux8Way(a, sel3); 
    expected.value = 128;
    ASSERT_EQ(result.value, expected.value);
}


