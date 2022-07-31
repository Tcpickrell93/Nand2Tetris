#include <gtest/gtest.h>
#include <tuple>

extern "C" 
{
#include "../src/logic_gates.h"
#include "../src/bits.h"
}

class LogicGatesTest : public ::testing::Test {
    protected:
        union bit1_u a = { .value = 0 };
        union bit1_u b = { .value = 0 };

        union bit1_u res_bit1 = { .value = 0 };
        union bit2_u res_bit2 = { .value = 0 };
        union bit4_u res_bit4 = { .value = 0 };
        union byte1_u res_byte1 = { .value = 0 };
        union byte2_u res_byte2 = { .value = 0 };

        union bit1_u sel = { .value = 0 };
        union bit2_u sel2 = { .value = 0 };
        union bit3_u sel3 = { .value = 0 };

        union byte1_u a8 = { .value = 0 };

        union byte2_u a16 = { .value = 0 };
        union byte2_u b16 = { .value = 65535 };
        union byte2_u c16 = { .value = 65280 };
        union byte2_u d16 = { .value = 255 };
        union byte2_u e16 = { .value = 61440 };
        union byte2_u f16 = { .value = 3840 };
        union byte2_u g16 = { .value = 240 };
        union byte2_u h16 = { .value = 15 };

        union bit1_u exp_bit1 = { .value = 0 };
        union bit2_u exp_bit2 = { .value = 0 };
        union bit4_u exp_bit4 = { .value = 0 };
        union byte2_u exp_byte2 = { .value = 0 };
        union byte1_u exp_byte1 = { .value = 0 };
};

/* 
-------------------------------------------------------------------------------
                            NAND GATE TESTS
-------------------------------------------------------------------------------
*/

class NandTest : public LogicGatesTest, 
                 public testing::WithParamInterface<std::tuple<int, int, int>> {
};

TEST_P(NandTest, ComparesNandOutputToExpected) {
    a.value = std::get<0>(GetParam());
    b.value = std::get<1>(GetParam());
    exp_bit1.value = std::get<2>(GetParam());
    Nand(&a, &b, &res_bit1);
    ASSERT_EQ(res_bit1.value, exp_bit1.value);
}

INSTANTIATE_TEST_SUITE_P(
    NandTestParameterized,
    NandTest,
    testing::Values(
        std::make_tuple(0, 0, 1),
        std::make_tuple(0, 1, 1),
        std::make_tuple(1, 0, 1),
        std::make_tuple(1, 1, 0)
    )
);

/* 
-------------------------------------------------------------------------------
                            NOT GATE TESTS
-------------------------------------------------------------------------------
*/

class NotTest : public LogicGatesTest, 
                public testing::WithParamInterface<std::tuple<int, int>> {
};

TEST_P(NotTest, ComparesNotOutputToExpected) {
    a.value = std::get<0>(GetParam());
    exp_bit1.value = std::get<1>(GetParam());
    Not(&a, &res_bit1);
    ASSERT_EQ(res_bit1.value, exp_bit1.value);
}

INSTANTIATE_TEST_SUITE_P(
    NotTestParameterized,
    NotTest,
    testing::Values(
        std::make_tuple(0, 1),
        std::make_tuple(1, 0)
    )
);

/* 
-------------------------------------------------------------------------------
                            AND GATE TESTS
-------------------------------------------------------------------------------
*/

class AndTest : public LogicGatesTest, 
                public testing::WithParamInterface<std::tuple<int, int, int>> {
};

TEST_P(AndTest, ComparesAndOutputToExpected) {
    a.value = std::get<0>(GetParam());
    b.value = std::get<1>(GetParam());
    exp_bit1.value = std::get<2>(GetParam());
    And(&a, &b, &res_bit1);
    ASSERT_EQ(res_bit1.value, exp_bit1.value);
}

INSTANTIATE_TEST_SUITE_P(
    AndTestParameterized,
    AndTest,
    testing::Values(
        std::make_tuple(0, 0, 0),
        std::make_tuple(0, 1, 0),
        std::make_tuple(1, 0, 0),
        std::make_tuple(1, 1, 1)
    )
);

/* 
-------------------------------------------------------------------------------
                            OR GATE TESTS
-------------------------------------------------------------------------------
*/

class OrTest : public LogicGatesTest, 
               public testing::WithParamInterface<std::tuple<int, int, int>> {
};

TEST_P(OrTest, ComparesOrOutputToExpected) {
    a.value = std::get<0>(GetParam());
    b.value = std::get<1>(GetParam());
    exp_bit1.value = std::get<2>(GetParam());
    Or(&a, &b, &res_bit1);
    ASSERT_EQ(res_bit1.value, exp_bit1.value);
}

INSTANTIATE_TEST_SUITE_P(
    OrTestParameterized,
    OrTest,
    testing::Values(
        std::make_tuple(0, 0, 0),
        std::make_tuple(0, 1, 1),
        std::make_tuple(1, 0, 1),
        std::make_tuple(1, 1, 1)
    )
);

/* 
-------------------------------------------------------------------------------
                            XOR GATE TESTS
-------------------------------------------------------------------------------
*/

class XorTest : public LogicGatesTest, 
                public testing::WithParamInterface<std::tuple<int, int, int>> {
};

TEST_P(XorTest, ComparesXorOutputToExpected) {
    a.value = std::get<0>(GetParam());
    b.value = std::get<1>(GetParam());
    exp_bit1.value = std::get<2>(GetParam());
    Xor(&a, &b, &res_bit1);
    ASSERT_EQ(res_bit1.value, exp_bit1.value);
}

INSTANTIATE_TEST_SUITE_P(
    XorTestParameterized,
    XorTest,
    testing::Values(
        std::make_tuple(0, 0, 0),
        std::make_tuple(0, 1, 1),
        std::make_tuple(1, 0, 1),
        std::make_tuple(1, 1, 0)
    )
);

/* 
-------------------------------------------------------------------------------
                            MUX GATE TESTS
-------------------------------------------------------------------------------
*/

class MuxTest : public LogicGatesTest, 
                public testing::WithParamInterface<std::tuple<int, int, int, int>> {
};

TEST_P(MuxTest, ComparesMuxOutputToExpected) {
    a.value = std::get<0>(GetParam());
    b.value = std::get<1>(GetParam());
    sel.value = std::get<2>(GetParam());
    exp_bit1.value = std::get<3>(GetParam());
    res_bit1 = *Mux(&a, &b, &sel);
    ASSERT_EQ(res_bit1.value, exp_bit1.value);
}

INSTANTIATE_TEST_SUITE_P(
    MuxTestParameterized,
    MuxTest,
    testing::Values(
        std::make_tuple(0, 0, 0, 0),
        std::make_tuple(0, 0, 1, 0),
        std::make_tuple(0, 1, 0, 0),
        std::make_tuple(0, 1, 1, 1),
        std::make_tuple(1, 0, 0, 1),
        std::make_tuple(1, 0, 1, 0),
        std::make_tuple(1, 1, 0, 1),
        std::make_tuple(1, 1, 1, 1)
    )
);

/* 
-------------------------------------------------------------------------------
                            DMUX GATE TESTS
-------------------------------------------------------------------------------
*/

class DMuxTest : public LogicGatesTest, 
                 public testing::WithParamInterface<std::tuple<int, int, int, int>> {
};

TEST_P(DMuxTest, ComparesDMuxOutputToExpected) {
    a.value = std::get<0>(GetParam());
    sel.value = std::get<1>(GetParam());
    exp_bit2.bit2_s.val1 = std::get<2>(GetParam());
    exp_bit2.bit2_s.val0 = std::get<3>(GetParam());
    DMux(&a, &sel, &res_bit2);
    ASSERT_EQ(res_bit2.bit2_s.val0, exp_bit2.bit2_s.val0);
    ASSERT_EQ(res_bit2.bit2_s.val1, exp_bit2.bit2_s.val1);
}

INSTANTIATE_TEST_SUITE_P(
    DMuxTestParameterized,
    DMuxTest,
    testing::Values(
        std::make_tuple(0, 0, 0, 0),
        std::make_tuple(0, 1, 0, 0),
        std::make_tuple(1, 0, 0, 1),
        std::make_tuple(1, 1, 1, 0)
    )
);

/* 
-------------------------------------------------------------------------------
                            ANDMUXOR GATE TESTS
-------------------------------------------------------------------------------
*/

class AndMuxOrTest : public LogicGatesTest, 
                     public testing::WithParamInterface<std::tuple<int, int, int, int>> {
};

TEST_P(AndMuxOrTest, ComparesAndMuxOrOutputToExpected) {
    a.value = std::get<0>(GetParam());
    b.value = std::get<1>(GetParam());
    sel.value = std::get<2>(GetParam());
    exp_bit1.value = std::get<3>(GetParam());
    AndMuxOr(&a, &b, &sel, &res_bit1);
    ASSERT_EQ(res_bit1.value, exp_bit1.value);
}

INSTANTIATE_TEST_SUITE_P(
    AndMuxOrTestParameterized,
    AndMuxOrTest,
    testing::Values(
        std::make_tuple(0, 0, 0, 0),
        std::make_tuple(1, 0, 0, 0),
        std::make_tuple(0, 1, 0, 0),
        std::make_tuple(1, 1, 0, 1),
        std::make_tuple(0, 0, 1, 0),
        std::make_tuple(1, 0, 1, 1),
        std::make_tuple(0, 1, 1, 1),
        std::make_tuple(1, 1, 1, 1)
    )
);

/* 
-------------------------------------------------------------------------------
                            NOT16 GATE TESTS
-------------------------------------------------------------------------------
*/

class Not16Test : public LogicGatesTest, 
                  public testing::WithParamInterface<std::tuple<int, int>> {
};

TEST_P(Not16Test, ComparesNot16OutputToExpected) {
    a16.value = std::get<0>(GetParam());
    exp_byte2.value = std::get<1>(GetParam());
    Not16(&a16, &res_byte2);
    ASSERT_EQ(res_byte2.value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Not16TestParameterized,
    Not16Test,
    testing::Values(
        std::make_tuple(0, 65535),
        std::make_tuple(65535, 0)
    )
);

/* 
-------------------------------------------------------------------------------
                            AND16 GATE TESTS
-------------------------------------------------------------------------------
*/

class And16Test : public LogicGatesTest, 
                  public testing::WithParamInterface<std::tuple<int, int, int>> {
};

TEST_P(And16Test, ComparesAnd16OutputToExpected) {
    a16.value = std::get<0>(GetParam());
    b16.value = std::get<1>(GetParam());
    exp_byte2.value = std::get<2>(GetParam());
    And16(&a16, &b16, &res_byte2);
    ASSERT_EQ(res_byte2.value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    And16TestParameterized,
    And16Test,
    testing::Values(
        std::make_tuple(65535, 65535, 65535),
        std::make_tuple(65535, 0, 0),
        std::make_tuple(0, 65535, 0),
        std::make_tuple(0, 0, 0),
        std::make_tuple(43690, 65535, 43690)
    )
);

/* 
-------------------------------------------------------------------------------
                            OR16 GATE TESTS
-------------------------------------------------------------------------------
*/

class Or16Test : public LogicGatesTest, 
                 public testing::WithParamInterface<std::tuple<int, int, int>> {
};

TEST_P(Or16Test, ComparesOr16OutputToExpected) {
    a16.value = std::get<0>(GetParam());
    b16.value = std::get<1>(GetParam());
    exp_byte2.value = std::get<2>(GetParam());
    Or16(&a16, &b16, &res_byte2);
    ASSERT_EQ(res_byte2.value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Or16TestParameterized,
    Or16Test,
    testing::Values(
        std::make_tuple(65535, 65535, 65535),
        std::make_tuple(65535, 0, 65535),
        std::make_tuple(0, 65535, 65535),
        std::make_tuple(0, 0, 0),
        std::make_tuple(43690, 65535, 65535)
    )
);

/* 
-------------------------------------------------------------------------------
                            MUX16 GATE TESTS
-------------------------------------------------------------------------------
*/

class Mux16Test : public LogicGatesTest, 
                  public testing::WithParamInterface<std::tuple<int, int, int, int>> {
};

TEST_P(Mux16Test, ComparesMux16OutputToExpected) {
    a16.value = std::get<0>(GetParam());
    b16.value = std::get<1>(GetParam());
    sel.value = std::get<2>(GetParam());
    exp_byte2.value = std::get<3>(GetParam());
    res_byte2 = *Mux16(&a16, &b16, &sel);
    ASSERT_EQ(res_byte2.value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Mux16TestParameterized,
    Mux16Test,
    testing::Values(
        std::make_tuple(0, 0, 0, 0),
        std::make_tuple(0, 0, 1, 0),
        std::make_tuple(0, 65535, 0, 0),
        std::make_tuple(0, 65535, 1, 65535),
        std::make_tuple(65535, 0, 0, 65535),
        std::make_tuple(65535, 0, 1, 0),
        std::make_tuple(65535, 43690, 0, 65535),
        std::make_tuple(65535, 43690, 1, 43690)
    )
);

/* 
-------------------------------------------------------------------------------
                            OR8WAY GATE TESTS
-------------------------------------------------------------------------------
*/

class Or8WayTest : public LogicGatesTest, 
                   public testing::WithParamInterface<std::tuple<int, int>> {
};

TEST_P(Or8WayTest, ComparesOr8WayOutputToExpected) {
    a8.value = std::get<0>(GetParam());
    exp_byte1.value = std::get<1>(GetParam());
    Or8Way(&a8, &res_byte1);
    ASSERT_EQ(res_byte1.value, exp_byte1.value);
}

INSTANTIATE_TEST_SUITE_P(
    Or8WayTestParameterized,
    Or8WayTest,
    testing::Values(
        std::make_tuple(0, 0),
        std::make_tuple(1, 1),
        std::make_tuple(456, 1),
        std::make_tuple(6851, 1),
        std::make_tuple(65535, 1)
    )
);

/* 
-------------------------------------------------------------------------------
                            MUX4WAY16 GATE TESTS
-------------------------------------------------------------------------------
*/

class Mux4Way16Test : public LogicGatesTest, 
                      public testing::WithParamInterface<std::tuple<int, int, int, int, int, int>> {
};

TEST_P(Mux4Way16Test, ComparesMux4Way16OutputToExpected) {
    a16.value = std::get<0>(GetParam());
    b16.value = std::get<1>(GetParam());
    c16.value = std::get<2>(GetParam());
    d16.value = std::get<3>(GetParam());
    sel2.value = std::get<4>(GetParam());
    exp_byte2.value = std::get<5>(GetParam());
    res_byte2 = *Mux4Way16(&a16, &b16, &c16, &d16, &sel2); 
    ASSERT_EQ(res_byte2.value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Mux4Way16TestParameterized,
    Mux4Way16Test,
    testing::Values(
        std::make_tuple(0, 65535, 65280, 255, 0, 0),
        std::make_tuple(0, 65535, 65280, 255, 1, 65535),
        std::make_tuple(0, 65535, 65280, 255, 2, 65280),
        std::make_tuple(0, 65535, 65280, 255, 3, 255)
    )
);

/* 
-------------------------------------------------------------------------------
                            MUX8WAY16 GATE TESTS
-------------------------------------------------------------------------------
*/

class Mux8Way16Test : public LogicGatesTest, 
                      public testing::WithParamInterface<std::tuple<int, int, int, int, int, int, int, int, int, int>> {
};

TEST_P(Mux8Way16Test, ComparesMux8Way16OutputToExpected) {
    a16.value = std::get<0>(GetParam());
    b16.value = std::get<1>(GetParam());
    c16.value = std::get<2>(GetParam());
    d16.value = std::get<3>(GetParam());
    e16.value = std::get<4>(GetParam());
    f16.value = std::get<5>(GetParam());
    g16.value = std::get<6>(GetParam());
    h16.value = std::get<7>(GetParam());
    sel3.value = std::get<8>(GetParam());
    exp_byte2.value = std::get<9>(GetParam());
    res_byte2 = *Mux8Way16(&a16, &b16, &c16, &d16, &e16, &f16, &g16, &h16, &sel3); 
    ASSERT_EQ(res_byte2.value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Mux8Way16TestParameterized,
    Mux8Way16Test,
    testing::Values(
        std::make_tuple(0, 65535, 65280, 255, 61440, 3840, 240, 15, 0, 0),
        std::make_tuple(0, 65535, 65280, 255, 61440, 3840, 240, 15, 1, 65535),
        std::make_tuple(0, 65535, 65280, 255, 61440, 3840, 240, 15, 2, 65280),
        std::make_tuple(0, 65535, 65280, 255, 61440, 3840, 240, 15, 3, 255),
        std::make_tuple(0, 65535, 65280, 255, 61440, 3840, 240, 15, 4, 61440),
        std::make_tuple(0, 65535, 65280, 255, 61440, 3840, 240, 15, 5, 3840),
        std::make_tuple(0, 65535, 65280, 255, 61440, 3840, 240, 15, 6, 240),
        std::make_tuple(0, 65535, 65280, 255, 61440, 3840, 240, 15, 7, 15)
    )
);

/* 
-------------------------------------------------------------------------------
                            DMUX4WAY GATE TESTS
-------------------------------------------------------------------------------
*/

class DMux4WayTest : public LogicGatesTest, 
                     public testing::WithParamInterface<std::tuple<int, int, int>> {
};

TEST_P(DMux4WayTest, ComparesDMux4WayOutputToExpected) {
    a.value = std::get<0>(GetParam());
    sel2.value = std::get<1>(GetParam());
    exp_bit4.value = std::get<2>(GetParam());
    DMux4Way(&a, &sel2, &res_bit4); 
    ASSERT_EQ(res_bit4.value, exp_bit4.value);
}

INSTANTIATE_TEST_SUITE_P(
    DMux4WayTestParameterized,
    DMux4WayTest,
    testing::Values(
        std::make_tuple(1, 0, 1),
        std::make_tuple(1, 1, 2),
        std::make_tuple(1, 2, 4),
        std::make_tuple(1, 3, 8)
    )
);

/* 
-------------------------------------------------------------------------------
                            DMUX8WAY GATE TESTS
-------------------------------------------------------------------------------
*/

class DMux8WayTest : public LogicGatesTest, 
                     public testing::WithParamInterface<std::tuple<int, int, int>> {
};

TEST_P(DMux8WayTest, ComparesDMux8WayOutputToExpected) {
    a.value = std::get<0>(GetParam());
    sel3.value = std::get<1>(GetParam());
    exp_byte1.value = std::get<2>(GetParam());
    DMux8Way(&a, &sel3, &res_byte1); 
    ASSERT_EQ(res_byte1.value, exp_byte1.value);
}

INSTANTIATE_TEST_SUITE_P(
    DMux8WayTestParameterized,
    DMux8WayTest,
    testing::Values(
        std::make_tuple(1, 0, 1),
        std::make_tuple(1, 1, 2),
        std::make_tuple(1, 2, 4),
        std::make_tuple(1, 3, 8),
        std::make_tuple(1, 4, 16),
        std::make_tuple(1, 5, 32),
        std::make_tuple(1, 6, 64),
        std::make_tuple(1, 7, 128)
    )
);


