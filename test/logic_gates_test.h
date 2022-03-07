#include "../src/logic_gates.h"

#include <gtest/gtest.h>


class LogicGatesTest : public ::testing::Test {
    protected:
        bit a{ 0b0u };
        bit b{ 0b0u };
        bit sel{ 0b0u };

        bit2 sel2{ 0b00u };
        
        bit3 sel3{ 0b00u };

        byte a8{ 0b0000'0000u };

        byte2 a16{ 0b0000'0000'0000'0000 };
        byte2 b16{ 0b1111'1111'1111'1111 };
        byte2 c16{ 0b1111'1111'0000'0000 };
        byte2 d16{ 0b0000'0000'1111'1111 };
        byte2 e16{ 0b1111'0000'0000'0000 };
        byte2 f16{ 0b0000'1111'0000'0000 };
        byte2 g16{ 0b0000'0000'1111'0000 };
        byte2 h16{ 0b0000'0000'0000'1111 };
};

TEST_F(LogicGatesTest, Nand) {
    // a=0, b=0
    ASSERT_TRUE(Nand(a, b)[0]);

    // a=1, b=0
    a.flip();
    ASSERT_TRUE(Nand(a, b)[0]);

    // a=1, b=1
    b.flip();
    ASSERT_FALSE(Nand(a, b)[0]);

    // a=0, b=1
    a.flip();
    ASSERT_TRUE(Nand(a, b)[0]);
}
    
TEST_F(LogicGatesTest, Not) {
    // a=0
    ASSERT_TRUE(Not(a)[0]);

    // a=1
    a.flip();
    ASSERT_FALSE(Not(a)[0]);
}

TEST_F(LogicGatesTest, And) {
    // a=0, b=0
    ASSERT_FALSE(And(a, b)[0]);

    // a=1, b=0
    a.flip();
    ASSERT_FALSE(And(a, b)[0]);

    // a=1, b=1
    b.flip();
    ASSERT_TRUE(And(a, b)[0]);

    // a=0, b=1
    a.flip();
    ASSERT_FALSE(And(a, b)[0]);
}

TEST_F(LogicGatesTest, Or) {
    // a=0, b=0
    ASSERT_FALSE(Or(a, b)[0]);

    // a=1, b=0
    a.flip();
    ASSERT_TRUE(Or(a, b)[0]);

    // a=1, b=1
    b.flip();
    ASSERT_TRUE(Or(a, b)[0]);

    // a=0, b=1
    a.flip();
    ASSERT_TRUE(Or(a, b)[0]);
}

TEST_F(LogicGatesTest, Xor) {
    // a=0, b=0
    ASSERT_FALSE(Xor(a, b)[0]);

    // a=1, b=0
    a.flip();
    ASSERT_TRUE(Xor(a, b)[0]);

    // a=1, b=1
    b.flip();
    ASSERT_FALSE(Xor(a, b)[0]);

    // a=0, b=1
    a.flip();
    ASSERT_TRUE(Xor(a, b)[0]);
}

TEST_F(LogicGatesTest, Mux) {
    // a=0, b=0, sel=0
    ASSERT_FALSE(Mux(a, b, sel)[0]);
    
    // a=0, b=0, sel=1
    sel.flip();
    ASSERT_FALSE(Mux(a, b, sel)[0]);

    // a=1, b=0, sel=1
    a.flip();
    ASSERT_FALSE(Mux(a, b, sel)[0]);

    // a=1, b=0, sel=0
    sel.flip();
    ASSERT_TRUE(Mux(a, b, sel)[0]);

    // a=1, b=1, sel=0
    b.flip();
    ASSERT_TRUE(Mux(a, b, sel)[0]);

    // a=1, b=1, sel=1
    sel.flip();
    ASSERT_TRUE(Mux(a, b, sel)[0]);

    // a=0, b=1, sel=1
    a.flip();
    ASSERT_TRUE(Mux(a, b, sel)[0]);

    // a=0, b=1, sel=0
    sel.flip();
    ASSERT_FALSE(Mux(a, b, sel)[0]);
}

TEST_F(LogicGatesTest, DMux) {
    // a=0, sel=0
    bit2 result{ DMux(a, sel) };
    ASSERT_FALSE(result[0]);
    ASSERT_FALSE(result[1]);
    
    // a=0, sel=1
    sel.flip();
    result = DMux(a, sel); 
    ASSERT_FALSE(result[0]);
    ASSERT_FALSE(result[1]);

    // a=1, sel=1
    a.flip();
    result = DMux(a, sel); 
    ASSERT_FALSE(result[0]);
    ASSERT_TRUE(result[1]);

    // a=1, sel=0
    sel.flip();
    result = DMux(a, sel); 
    ASSERT_TRUE(result[0]);
    ASSERT_FALSE(result[1]);
}

TEST_F(LogicGatesTest, AndMuxOr) {
    // a=1, b=0, sel=1
    sel.flip();
    a.flip();
    ASSERT_EQ(AndMuxOr(a, b, sel)[0], Or(a, b)[0]);

    // a=1, b=0, sel=0
    sel.flip();
    ASSERT_EQ(AndMuxOr(a, b, sel)[0], And(a, b)[0]);
}

TEST_F(LogicGatesTest, Not16) {
    byte2 result{ Not16(a16) };
    for (int i = 0; i < 16; i++) {
        ASSERT_TRUE(result[i]);
    }
}

TEST_F(LogicGatesTest, And16) {
    // a16=0000'0000'0000'0000
    // b16=0000'0000'0000'0000
    b16.flip();
    byte2 result{ And16(a16, b16) };
    for (int i = 0; i < 16; i++) {
        ASSERT_FALSE(result[i]);
    }

    // a16=1111'1111'1111'1111
    // b16=0000'0000'0000'0000
    a16.flip();
    result = And16(a16, b16);
    for (int i = 0; i < 16; i++) {
        ASSERT_FALSE(result[i]);
    }

    // a16=1111'1111'1111'1111
    // b16=1111'1111'1111'1111
    b16.flip();
    result = And16(a16, b16);
    for (int i = 0; i < 16; i++) {
        ASSERT_TRUE(result[i]);
    }

    // a16=0000'0000'0000'0000
    // b16=1111'1111'1111'1111
    a16.flip();
    result = And16(a16, b16);
    for (int i = 0; i < 16; i++) {
        ASSERT_FALSE(result[i]);
    }
}

TEST_F(LogicGatesTest, Or16) {
    // a16=0000'0000'0000'0000
    // b16=0000'0000'0000'0000
    b16.flip();
    byte2 result{ Or16(a16, b16) };
    for (int i = 0; i < 16; i++) {
        ASSERT_FALSE(result[i]);
    }

    // a16=1111'1111'1111'1111
    // b16=0000'0000'0000'0000
    a16.flip();
    result = Or16(a16, b16);
    for (int i = 0; i < 16; i++) {
        ASSERT_TRUE(result[i]);
    }

    // a16=1111'1111'1111'1111
    // b16=1111'1111'1111'1111
    b16.flip();
    result = Or16(a16, b16);
    for (int i = 0; i < 16; i++) {
        ASSERT_TRUE(result[i]);
    }

    // a16=0000'0000'0000'0000
    // b16=1111'1111'1111'1111
    a16.flip();
    result = Or16(a16, b16);
    for (int i = 0; i < 16; i++) {
        ASSERT_TRUE(result[i]);
    }
}

TEST_F(LogicGatesTest, Mux16) {
    // a16=1111'1111'1111'1111
    // b16=0000'0000'0000'0000
    // sel=0
    b16.flip();
    a16.flip();
    byte2 result{ Mux16(a16, b16, sel) };
    ASSERT_EQ(result, a16);

    // a16=1111'1111'1111'1111
    // b16=0000'0000'0000'0000
    // sel=1
    sel.flip();
    result = Mux16(a16, b16, sel);
    ASSERT_EQ(result, b16);
}

TEST_F(LogicGatesTest, Or8Way) {
    // a8=0000'0000
    ASSERT_FALSE(Or8Way(a8)[0]);

    a8[3].flip();
    ASSERT_TRUE(Or8Way(a8)[0]);
}

TEST_F(LogicGatesTest, Mux4Way16) {
    // a16=0000'0000'0000'0000
    // b16=1111'1111'1111'1111
    // c16=1111'1111'0000'0000
    // d16=0000'0000'1111'1111

    // sel2=00
    byte2 result{ Mux4Way16(a16, b16, c16, d16, sel2) };
    ASSERT_EQ(result, a16);

    // sel2=01
    sel2.set(0);
    result = Mux4Way16(a16, b16, c16, d16, sel2); 
    ASSERT_EQ(result, b16);

    // sel2=10
    sel2.set(1);
    sel2.reset(0);
    result = Mux4Way16(a16, b16, c16, d16, sel2); 
    ASSERT_EQ(result, c16);
    
    // sel2=11
    sel2.set(0);
    result = Mux4Way16(a16, b16, c16, d16, sel2); 
    ASSERT_EQ(result, d16);
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
    byte2 result{ Mux8Way16(a16, b16, c16, d16, e16, f16, g16, h16, sel3) };
    ASSERT_EQ(result, a16);

    // sel3=001
    sel3.set(0);
    result = Mux8Way16(a16, b16, c16, d16, e16, f16, g16, h16, sel3); 
    ASSERT_EQ(result, b16);

    // sel3=010
    sel3.reset(0);
    sel3.set(1);
    result = Mux8Way16(a16, b16, c16, d16, e16, f16, g16, h16, sel3); 
    ASSERT_EQ(result, c16);

    // sel3=011
    sel3.set(0);
    result = Mux8Way16(a16, b16, c16, d16, e16, f16, g16, h16, sel3); 
    ASSERT_EQ(result, d16);

    // sel3=100
    sel3.set(2);
    sel3.reset(1);
    sel3.reset(0);
    result = Mux8Way16(a16, b16, c16, d16, e16, f16, g16, h16, sel3); 
    ASSERT_EQ(result, e16);

    // sel3=101
    sel3.set(0);
    result = Mux8Way16(a16, b16, c16, d16, e16, f16, g16, h16, sel3); 
    ASSERT_EQ(result, f16);

    // sel3=110
    sel3.set(1);
    sel3.reset(0);
    result = Mux8Way16(a16, b16, c16, d16, e16, f16, g16, h16, sel3); 
    ASSERT_EQ(result, g16);

    // sel3=111
    sel3.set(0);
    result = Mux8Way16(a16, b16, c16, d16, e16, f16, g16, h16, sel3); 
    ASSERT_EQ(result, h16);
}

TEST_F(LogicGatesTest, DMux4Way) {
    // a=1, sel2=00
    a.flip();
    bit4 result{ DMux4Way(a, sel2) }; 
    bit4 expected{ 0b0001u };
    ASSERT_EQ(result, expected);

    // a=1, sel=01
    sel2.set(0);
    result = DMux4Way(a, sel2); 
    expected = 0b0010u;
    ASSERT_EQ(result, expected);

    // a=1, sel=10
    sel2.set(1);
    sel2.reset(0);
    result = DMux4Way(a, sel2); 
    expected = 0b0100u;
    ASSERT_EQ(result, expected);

    // a=1, sel=11
    sel2.set(0);
    result = DMux4Way(a, sel2); 
    expected = 0b1000u;
    ASSERT_EQ(result, expected);
}

TEST_F(LogicGatesTest, DMux8Way) {
    // a=1, sel3=000
    a.flip();
    byte result{ DMux8Way(a, sel3) }; 
    byte expected{ 0b0000'0001u };
    ASSERT_EQ(result, expected);

    // a=1, sel3=001
    sel3.set(0);
    result = DMux8Way(a, sel3); 
    expected = 0b0000'0010u;
    ASSERT_EQ(result, expected);

    // a=1, sel=010
    sel3.set(1);
    sel3.reset(0);
    result = DMux8Way(a, sel3); 
    expected = 0b0000'0100u;
    ASSERT_EQ(result, expected);

    // a=1, sel=011
    sel3.set(0);
    result = DMux8Way(a, sel3); 
    expected = 0b0000'1000u;
    ASSERT_EQ(result, expected);

    // a=1, sel=100
    sel3.set(2);
    sel3.reset(1);
    sel3.reset(0);
    result = DMux8Way(a, sel3); 
    expected = 0b0001'0000u;
    ASSERT_EQ(result, expected);

    // a=1, sel=101
    sel3.set(0);
    result = DMux8Way(a, sel3); 
    expected = 0b0010'0000u;
    ASSERT_EQ(result, expected);

    // a=1, sel=110
    sel3.set(1);
    sel3.reset(0);
    result = DMux8Way(a, sel3); 
    expected = 0b0100'0000u;
    ASSERT_EQ(result, expected);

    // a=1, sel=111
    sel3.set(0);
    result = DMux8Way(a, sel3); 
    expected = 0b1000'0000u;
    ASSERT_EQ(result, expected);
}


