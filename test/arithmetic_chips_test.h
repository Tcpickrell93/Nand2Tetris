#include <gtest/gtest.h>
#include <tuple>

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

        union byte2_u* p_res_byte2 = &res_byte2;

        union bit1_u exp_bit1 = { .value = 0 };
        union bit2_u exp_bit2 = { .value = 0 };
        union bit4_u exp_bit4 = { .value = 0 };
        union byte2_u exp_byte2 = { .value = 0 };
        union byte1_u exp_byte1 = { .value = 0 };
        
        union byte2_u exp_out = { .value = 0 };
        union bit1_u exp_zr = { .value = 0 };
        union bit1_u exp_ng = { .value = 0 };
};

/* 
-------------------------------------------------------------------------------
                            HALF ADDER TESTS
-------------------------------------------------------------------------------
*/

class HalfAdderTest : public ArithmeticChipsTest, 
                      public testing::WithParamInterface<std::tuple<int, int, int>> {
};

TEST_P(HalfAdderTest, ComparesHalfAdderOutputToExpected) {
    a.value = std::get<0>(GetParam());
    b.value = std::get<1>(GetParam());
    exp_bit2.value = std::get<2>(GetParam());
    HalfAdder(&a, &b, &res_bit2);
    ASSERT_EQ(res_bit2.value, exp_bit2.value);
}

INSTANTIATE_TEST_SUITE_P(
    HalfAdderTestParameterized,
    HalfAdderTest,
    testing::Values(
        std::make_tuple(0, 0, 0),
        std::make_tuple(0, 1, 1),
        std::make_tuple(1, 0, 1),
        std::make_tuple(1, 1, 2)
    )
);

/* 
-------------------------------------------------------------------------------
                            FULL ADDER TESTS
-------------------------------------------------------------------------------
*/

class FullAdderTest : public ArithmeticChipsTest, 
                      public testing::WithParamInterface<std::tuple<int, int, int, int>> {
};

TEST_P(FullAdderTest, ComparesFullAdderOutputToExpected) {
    a.value = std::get<0>(GetParam());
    b.value = std::get<1>(GetParam());
    c.value = std::get<2>(GetParam());
    exp_bit2.value = std::get<3>(GetParam());
    FullAdder(&a, &b, &c, &res_bit2);
    ASSERT_EQ(res_bit2.value, exp_bit2.value);
}

INSTANTIATE_TEST_SUITE_P(
    FullAdderTestParameterized,
    FullAdderTest,
    testing::Values(
        std::make_tuple(0, 0, 0, 0),
        std::make_tuple(0, 0, 1, 1),
        std::make_tuple(0, 1, 0, 1),
        std::make_tuple(0, 1, 1, 2),
        std::make_tuple(1, 0, 0, 1),
        std::make_tuple(1, 0, 1, 2),
        std::make_tuple(1, 1, 0, 2),
        std::make_tuple(1, 1, 1, 3)
    )
);

/* 
-------------------------------------------------------------------------------
                            ADD16 TESTS
-------------------------------------------------------------------------------
*/

class Add16Test : public ArithmeticChipsTest, 
                  public testing::WithParamInterface<std::tuple<int, int, int>> {
};

TEST_P(Add16Test, ComparesAdd16OutputToExpected) {
    a16.value = std::get<0>(GetParam());
    b16.value = std::get<1>(GetParam());
    exp_byte2.value = std::get<2>(GetParam());
    Add16(&a16, &b16, &res_byte2);
    ASSERT_EQ(res_byte2.value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Add16TestParameterized,
    Add16Test,
    testing::Values(
        std::make_tuple(240, 15, 255),
        std::make_tuple(1000, 2000, 3000),
        std::make_tuple(0, 0, 0)
    )
);


/* 
-------------------------------------------------------------------------------
                            INC16 TESTS
-------------------------------------------------------------------------------
*/

class Inc16Test : public ArithmeticChipsTest, 
                  public testing::WithParamInterface<std::tuple<int, int>> {
};

TEST_P(Inc16Test, ComparesInc16OutputToExpected) {
    a16.value = std::get<0>(GetParam());
    exp_byte2.value = std::get<1>(GetParam());
    res_byte2 = Inc16(&a16);
    ASSERT_EQ(res_byte2.value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Inc16TestParameterized,
    Inc16Test,
    testing::Values(
        std::make_tuple(240, 241),
        std::make_tuple(1000, 1001),
        std::make_tuple(0, 1),
        std::make_tuple(65535, 0)
    )
);

/*
-------------------------------------------------------------------------------
                            ALU TESTS
-------------------------------------------------------------------------------
*/

class ALUTest : public ArithmeticChipsTest, 
                public testing::WithParamInterface<std::tuple<int, int, int, int, int, int, int, int, int, int, int>> {
};

TEST_P(ALUTest, ComparesALUOutputToExpected) {
    a16.value = std::get<0>(GetParam());
    b16.value = std::get<1>(GetParam());
    za.value = std::get<2>(GetParam());
    na.value = std::get<3>(GetParam());
    zb.value = std::get<4>(GetParam());
    nb.value = std::get<5>(GetParam());
    f.value = std::get<6>(GetParam());
    no.value = std::get<7>(GetParam());
    exp_out.value = std::get<8>(GetParam());
    exp_zr.value = std::get<9>(GetParam());
    exp_ng.value = std::get<10>(GetParam());
    ALU(&a16, &b16, &za, &na, &zb, &nb, &f, &no, &zr, &ng, &res_byte2);
    ASSERT_EQ(res_byte2.value, exp_out.value);
    ASSERT_EQ(zr.value, exp_zr.value);
    ASSERT_EQ(ng.value, exp_ng.value);
}

INSTANTIATE_TEST_SUITE_P(
    ALUTestParameterized,
    ALUTest,
    testing::Values(
        std::make_tuple(240, 15, 1, 0, 1, 0, 1, 0, 0, 1, 0),
        std::make_tuple(240, 15, 1, 1, 1, 1, 1, 1, 1, 0, 0),
        std::make_tuple(240, 15, 1, 1, 1, 0, 1, 0, 65535, 0, 1),
        std::make_tuple(240, 15, 0, 0, 1, 1, 0, 0, 240, 0, 0),
        std::make_tuple(240, 15, 1, 1, 0, 0, 0, 0, 15, 0, 0),
        std::make_tuple(240, 15, 0, 0, 1, 1, 0, 1, 65295, 0, 1),
        std::make_tuple(240, 15, 1, 1, 0, 0, 0, 1, 65520, 0, 1),
        std::make_tuple(240, 15, 0, 0, 1, 1, 1, 1, 65296, 0, 1),
        std::make_tuple(240, 15, 1, 1, 0, 0, 1, 1, 65521, 0, 1),
        std::make_tuple(240, 15, 0, 1, 1, 1, 1, 1, 241, 0, 0),
        std::make_tuple(240, 15, 1, 1, 0, 1, 1, 1, 16, 0, 0),
        std::make_tuple(240, 15, 0, 0, 1, 1, 1, 0, 239, 0, 0),
        std::make_tuple(240, 15, 1, 1, 0, 0, 1, 0, 14, 0, 0),
        std::make_tuple(240, 15, 0, 0, 0, 0, 1, 0, 255, 0, 0),
        std::make_tuple(240, 15, 0, 1, 0, 0, 1, 1, 225, 0, 0),
        std::make_tuple(240, 15, 0, 0, 0, 1, 1, 1, 65311, 0, 1),
        std::make_tuple(240, 15, 0, 0, 0, 0, 0, 0, 0, 1, 0),
        std::make_tuple(240, 15, 0, 1, 0, 1, 0, 1, 255, 0, 0)
    )
);
