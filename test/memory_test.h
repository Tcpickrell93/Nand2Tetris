#include <gtest/gtest.h>
#include <tuple>

extern "C"
{
#include "../src/memory.h"
#include "../src/bits.h"
}

class MemoryTest: public ::testing::Test {
    protected:
        union bit1_u in = { .value = 0 };
        union byte2_u in16 = { .value = 0 };

        union bit1_u load = { .value = 0 };

        union bit3_u addr_bit3 = { .value = 0 };
        union bit6_u addr_bit6 = { .value = 0 };
        union bit9_u addr_bit9 = { .value = 0 };
        union bit12_u addr_bit12 = { .value = 0 };
        union bit14_u addr_bit14 = { .value = 0 };

        union byte2_u res_byte2 = { .value = 0 };
        union byte2_u* p_res_byte2 = &res_byte2;

        union bit1_u exp_bit1 = { .value = 0 };
        union byte2_u exp_byte2 = { .value = 0 };
};

/* 
-------------------------------------------------------------------------------
                            REGISTER BIT TESTS
-------------------------------------------------------------------------------
*/

class RegisterBitTest : public MemoryTest, 
                        public testing::WithParamInterface<std::tuple<int, int, int>> {
    protected:
        RegisterBit_u reg_bit = { .value = 0 };
};

TEST_P(RegisterBitTest, ComparesRegisterBitOutputToExpected) {
    in.value = std::get<0>(GetParam());
    load.value = std::get<1>(GetParam());
    exp_bit1.value = std::get<2>(GetParam());
    UpdateRegisterBit(&reg_bit, &in, &load);
    ASSERT_EQ(reg_bit.value, exp_bit1.value);
}

INSTANTIATE_TEST_SUITE_P(
    RegisterBitTestParameterized,
    RegisterBitTest,
    testing::Values(
        std::make_tuple(0, 0, 0),
        std::make_tuple(0, 1, 0),
        std::make_tuple(1, 0, 0),
        std::make_tuple(1, 1, 1)
    )
);

/* 
-------------------------------------------------------------------------------
                            REGISTER16 TESTS
-------------------------------------------------------------------------------
*/

class Register16Test : public MemoryTest, 
                       public testing::WithParamInterface<std::tuple<int, int, int>> {
    protected:
        Register16_u reg16 = { .value = 0 };
};

TEST_P(Register16Test, ComparesRegister16OutputToExpected) {
    in16.value = std::get<0>(GetParam());
    load.value = std::get<1>(GetParam());
    exp_byte2.value = std::get<2>(GetParam());
    UpdateRegister16(&reg16, &in16, &load);
    ASSERT_EQ(reg16.value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Register16TestParameterized,
    Register16Test,
    testing::Values(
        std::make_tuple(0, 0, 0),
        std::make_tuple(0, 1, 0),
        std::make_tuple(65535, 0, 0),
        std::make_tuple(65535, 1, 65535)
    )
);

/* 
-------------------------------------------------------------------------------
                            RAM8 READ TESTS
-------------------------------------------------------------------------------
*/

class Ram8Read : public MemoryTest, 
                 public testing::WithParamInterface<std::tuple<int, int>> {
    protected:
        struct RAM8 ram8 = { 0 };

        void SetUp() override {
            ram8.reg0.value = 0;
            ram8.reg1.value = 1;
            ram8.reg2.value = 2;
            ram8.reg3.value = 3;
            ram8.reg4.value = 4;
            ram8.reg5.value = 5;
            ram8.reg6.value = 6;
            ram8.reg7.value = 7;
        }
};

TEST_P(Ram8Read, ComparesRam8OutputWithValuesToExpected) {
    addr_bit3.value = std::get<0>(GetParam());
    exp_byte2.value = std::get<1>(GetParam());
    p_res_byte2 = ReadRAM8(&ram8, &addr_bit3);
    ASSERT_EQ(p_res_byte2->value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Ram8ReadWithValuesParameterized,
    Ram8Read,
    testing::Values(
        std::make_tuple(0, 0),
        std::make_tuple(1, 1),
        std::make_tuple(2, 2),
        std::make_tuple(3, 3),
        std::make_tuple(4, 4),
        std::make_tuple(5, 5),
        std::make_tuple(6, 6),
        std::make_tuple(7, 7)
    )
);

/* 
-------------------------------------------------------------------------------
                            RAM8 WRITE TESTS
-------------------------------------------------------------------------------
*/

class Ram8Write : public MemoryTest, 
                  public testing::WithParamInterface<std::tuple<int, int, int, int>> {
    protected:
        struct RAM8 ram8 = { 0 };
};

TEST_P(Ram8Write, ComparesRam8WrittenOutputToExpected) {
    addr_bit3.value = std::get<0>(GetParam());
    in16.value = std::get<1>(GetParam());
    load.value = std::get<2>(GetParam());
    exp_byte2.value = std::get<3>(GetParam());
    WriteRAM8(&ram8, &addr_bit3, &in16, &load);
    p_res_byte2 = ReadRAM8(&ram8, &addr_bit3);
    ASSERT_EQ(p_res_byte2->value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Ram8WriteParameterized,
    Ram8Write,
    testing::Values(
        std::make_tuple(0, 123, 0, 0),
        std::make_tuple(0, 123, 1, 123),
        std::make_tuple(1, 456, 0, 0),
        std::make_tuple(1, 456, 1, 456),
        std::make_tuple(2, 789, 0, 0),
        std::make_tuple(2, 789, 1, 789),
        std::make_tuple(3, 123, 0, 0),
        std::make_tuple(3, 123, 1, 123),
        std::make_tuple(4, 456, 0, 0),
        std::make_tuple(4, 456, 1, 456),
        std::make_tuple(5, 789, 0, 0),
        std::make_tuple(5, 789, 1, 789),
        std::make_tuple(6, 123, 0, 0),
        std::make_tuple(6, 123, 1, 123),
        std::make_tuple(7, 456, 0, 0),
        std::make_tuple(7, 456, 1, 456)
    )
);

/* 
-------------------------------------------------------------------------------
                            RAM64 READ TESTS
-------------------------------------------------------------------------------
*/

class Ram64Read : public MemoryTest, 
                  public testing::WithParamInterface<std::tuple<int, int>> {
    protected:
        struct RAM64 ram64 = { 0 };

        void SetUp() override {
            // Write to a different reg16 location in each ram8
            load.value = 1;
            WriteRAM8(&ram64.ram0, &addr_bit3, &in16, &load);
            addr_bit3.value += 1;
            in16.value += 2;
            WriteRAM8(&ram64.ram1, &addr_bit3, &in16, &load);
            addr_bit3.value += 1;
            in16.value += 2;
            WriteRAM8(&ram64.ram2, &addr_bit3, &in16, &load);
            addr_bit3.value += 1;
            in16.value += 2;
            WriteRAM8(&ram64.ram3, &addr_bit3, &in16, &load);
            addr_bit3.value += 1;
            in16.value += 2;
            WriteRAM8(&ram64.ram4, &addr_bit3, &in16, &load);
            addr_bit3.value += 1;
            in16.value += 2;
            WriteRAM8(&ram64.ram5, &addr_bit3, &in16, &load);
            addr_bit3.value += 1;
            in16.value += 2;
            WriteRAM8(&ram64.ram6, &addr_bit3, &in16, &load);
            addr_bit3.value += 1;
            in16.value += 2;
            WriteRAM8(&ram64.ram7, &addr_bit3, &in16, &load);
        }
};

TEST_P(Ram64Read, ComparesRam64OutputWithValuesToExpected) {
    addr_bit6.value = std::get<0>(GetParam());
    exp_byte2.value = std::get<1>(GetParam());
    p_res_byte2 = ReadRAM64(&ram64, &addr_bit6);
    ASSERT_EQ(p_res_byte2->value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Ram64ReadWithValuesParameterized,
    Ram64Read,
    testing::Values(
        std::make_tuple(0, 0),
        std::make_tuple(9, 2),
        std::make_tuple(18, 4),
        std::make_tuple(27, 6),
        std::make_tuple(36, 8),
        std::make_tuple(45, 10),
        std::make_tuple(54, 12),
        std::make_tuple(63, 14)
    )
);

/* 
-------------------------------------------------------------------------------
                            RAM64 WRITE TESTS
-------------------------------------------------------------------------------
*/

class Ram64Write : public MemoryTest, 
                   public testing::WithParamInterface<std::tuple<int, int, int, int>> {
    protected:
        struct RAM64 ram64 = { 0 };
};

TEST_P(Ram64Write, ComparesRam64WrittenOutputToExpected) {
    addr_bit6.value = std::get<0>(GetParam());
    in16.value = std::get<1>(GetParam());
    load.value = std::get<2>(GetParam());
    exp_byte2.value = std::get<3>(GetParam());
    WriteRAM64(&ram64, &addr_bit6, &in16, &load);
    p_res_byte2 = ReadRAM64(&ram64, &addr_bit6);
    ASSERT_EQ(p_res_byte2->value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Ram64WriteParameterized,
    Ram64Write,
    testing::Values(
        std::make_tuple(0, 123, 0, 0),
        std::make_tuple(0, 123, 1, 123),
        std::make_tuple(9, 456, 0, 0),
        std::make_tuple(9, 456, 1, 456),
        std::make_tuple(18, 789, 0, 0),
        std::make_tuple(18, 789, 1, 789),
        std::make_tuple(27, 123, 0, 0),
        std::make_tuple(27, 123, 1, 123),
        std::make_tuple(36, 456, 0, 0),
        std::make_tuple(36, 456, 1, 456),
        std::make_tuple(45, 789, 0, 0),
        std::make_tuple(45, 789, 1, 789),
        std::make_tuple(54, 123, 0, 0),
        std::make_tuple(54, 123, 1, 123),
        std::make_tuple(63, 456, 0, 0),
        std::make_tuple(63, 456, 1, 456)
    )
);

/* 
-------------------------------------------------------------------------------
                            RAM512 READ TESTS
-------------------------------------------------------------------------------
*/

class Ram512Read : public MemoryTest, 
                   public testing::WithParamInterface<std::tuple<int, int>> {
    protected:
        struct RAM512 ram512 = { 0 };

        void SetUp() override {
            // Write to a different ram8 location in each ram64
            load.value = 1;
            WriteRAM64(&ram512.ram0, &addr_bit6, &in16, &load);
            addr_bit6.value += 9;
            in16.value += 2;
            WriteRAM64(&ram512.ram1, &addr_bit6, &in16, &load);
            addr_bit6.value += 9;
            in16.value += 2;
            WriteRAM64(&ram512.ram2, &addr_bit6, &in16, &load);
            addr_bit6.value += 9;
            in16.value += 2;
            WriteRAM64(&ram512.ram3, &addr_bit6, &in16, &load);
            addr_bit6.value += 9;
            in16.value += 2;
            WriteRAM64(&ram512.ram4, &addr_bit6, &in16, &load);
            addr_bit6.value += 9;
            in16.value += 2;
            WriteRAM64(&ram512.ram5, &addr_bit6, &in16, &load);
            addr_bit6.value += 9;
            in16.value += 2;
            WriteRAM64(&ram512.ram6, &addr_bit6, &in16, &load);
            addr_bit6.value += 9;
            in16.value += 2;
            WriteRAM64(&ram512.ram7, &addr_bit6, &in16, &load);
        }
};

TEST_P(Ram512Read, ComparesRam512OutputWithValuesToExpected) {
    addr_bit9.value = std::get<0>(GetParam());
    exp_byte2.value = std::get<1>(GetParam());
    p_res_byte2 = ReadRAM512(&ram512, &addr_bit9);
    ASSERT_EQ(p_res_byte2->value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Ram512ReadWithValuesParameterized,
    Ram512Read,
    testing::Values(
        std::make_tuple(0, 0),
        std::make_tuple(73, 2),
        std::make_tuple(146, 4),
        std::make_tuple(219, 6),
        std::make_tuple(292, 8),
        std::make_tuple(365, 10),
        std::make_tuple(438, 12),
        std::make_tuple(511, 14)
    )
);

/* 
-------------------------------------------------------------------------------
                            RAM512 WRITE TESTS
-------------------------------------------------------------------------------
*/

class Ram512Write : public MemoryTest, 
                    public testing::WithParamInterface<std::tuple<int, int, int, int>> {
    protected:
        struct RAM512 ram512 = { 0 };
};

TEST_P(Ram512Write, ComparesRam512WrittenOutputToExpected) {
    addr_bit9.value = std::get<0>(GetParam());
    in16.value = std::get<1>(GetParam());
    load.value = std::get<2>(GetParam());
    exp_byte2.value = std::get<3>(GetParam());
    WriteRAM512(&ram512, &addr_bit9, &in16, &load);
    p_res_byte2 = ReadRAM512(&ram512, &addr_bit9);
    ASSERT_EQ(p_res_byte2->value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Ram512WriteParameterized,
    Ram512Write,
    testing::Values(
        std::make_tuple(0, 123, 0, 0),
        std::make_tuple(0, 123, 1, 123),
        std::make_tuple(73, 456, 0, 0),
        std::make_tuple(73, 456, 1, 456),
        std::make_tuple(146, 789, 0, 0),
        std::make_tuple(146, 789, 1, 789),
        std::make_tuple(219, 123, 0, 0),
        std::make_tuple(219, 123, 1, 123),
        std::make_tuple(292, 456, 0, 0),
        std::make_tuple(292, 456, 1, 456),
        std::make_tuple(365, 789, 0, 0),
        std::make_tuple(365, 789, 1, 789),
        std::make_tuple(438, 123, 0, 0),
        std::make_tuple(438, 123, 1, 123),
        std::make_tuple(511, 456, 0, 0),
        std::make_tuple(511, 456, 1, 456)
    )
);

/* 
-------------------------------------------------------------------------------
                            RAM4k READ TESTS
-------------------------------------------------------------------------------
*/

class Ram4kRead : public MemoryTest, 
                  public testing::WithParamInterface<std::tuple<int, int>> {
    protected:
        struct RAM4k ram4k = { 0 };

        void SetUp() override {
            // Write to a different ram8 location in each ram64
            load.value = 1;
            WriteRAM512(&ram4k.ram0, &addr_bit9, &in16, &load);
            addr_bit9.value += 73;
            in16.value += 2;
            WriteRAM512(&ram4k.ram1, &addr_bit9, &in16, &load);
            addr_bit9.value += 73;
            in16.value += 2;
            WriteRAM512(&ram4k.ram2, &addr_bit9, &in16, &load);
            addr_bit9.value += 73;
            in16.value += 2;
            WriteRAM512(&ram4k.ram3, &addr_bit9, &in16, &load);
            addr_bit9.value += 73;
            in16.value += 2;
            WriteRAM512(&ram4k.ram4, &addr_bit9, &in16, &load);
            addr_bit9.value += 73;
            in16.value += 2;
            WriteRAM512(&ram4k.ram5, &addr_bit9, &in16, &load);
            addr_bit9.value += 73;
            in16.value += 2;
            WriteRAM512(&ram4k.ram6, &addr_bit9, &in16, &load);
            addr_bit9.value += 73;
            in16.value += 2;
            WriteRAM512(&ram4k.ram7, &addr_bit9, &in16, &load);
        }
};

TEST_P(Ram4kRead, ComparesRam4kOutputWithValuesToExpected) {
    addr_bit12.value = std::get<0>(GetParam());
    exp_byte2.value = std::get<1>(GetParam());
    p_res_byte2 = ReadRAM4k(&ram4k, &addr_bit12);
    ASSERT_EQ(p_res_byte2->value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Ram4kReadWithValuesParameterized,
    Ram4kRead,
    testing::Values(
        std::make_tuple(0, 0),
        std::make_tuple(585, 2),
        std::make_tuple(1170, 4),
        std::make_tuple(1755, 6),
        std::make_tuple(2340, 8),
        std::make_tuple(2925, 10),
        std::make_tuple(3510, 12),
        std::make_tuple(4095, 14)
    )
);

/* 
-------------------------------------------------------------------------------
                            RAM4k WRITE TESTS
-------------------------------------------------------------------------------
*/

class Ram4kWrite : public MemoryTest, 
                   public testing::WithParamInterface<std::tuple<int, int, int, int>> {
    protected:
        struct RAM4k ram4k = { 0 };
};

TEST_P(Ram4kWrite, ComparesRam4kWrittenOutputToExpected) {
    addr_bit12.value = std::get<0>(GetParam());
    in16.value = std::get<1>(GetParam());
    load.value = std::get<2>(GetParam());
    exp_byte2.value = std::get<3>(GetParam());
    WriteRAM4k(&ram4k, &addr_bit12, &in16, &load);
    p_res_byte2 = ReadRAM4k(&ram4k, &addr_bit12);
    ASSERT_EQ(p_res_byte2->value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Ram4kWriteParameterized,
    Ram4kWrite,
    testing::Values(
        std::make_tuple(0, 123, 0, 0),
        std::make_tuple(0, 123, 1, 123),
        std::make_tuple(585, 456, 0, 0),
        std::make_tuple(585, 456, 1, 456),
        std::make_tuple(1170, 789, 0, 0),
        std::make_tuple(1170, 789, 1, 789),
        std::make_tuple(1755, 123, 0, 0),
        std::make_tuple(1755, 123, 1, 123),
        std::make_tuple(2340, 456, 0, 0),
        std::make_tuple(2340, 456, 1, 456),
        std::make_tuple(2925, 789, 0, 0),
        std::make_tuple(2925, 789, 1, 789),
        std::make_tuple(3510, 123, 0, 0),
        std::make_tuple(3510, 123, 1, 123),
        std::make_tuple(4095, 456, 0, 0),
        std::make_tuple(4095, 456, 1, 456)
    )
);
/*
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
*/

/* 
-------------------------------------------------------------------------------
                            RAM16k READ TESTS
-------------------------------------------------------------------------------
*/

class Ram16kRead : public MemoryTest, 
                   public testing::WithParamInterface<std::tuple<int, int>> {
    protected:
        struct RAM16k ram16k = { 0 };

        void SetUp() override {
            // Write to a different ram8 location in each ram64
            load.value = 1;
            WriteRAM4k(&ram16k.ram0, &addr_bit12, &in16, &load);
            addr_bit12.value += 585;
            in16.value += 2;
            WriteRAM4k(&ram16k.ram1, &addr_bit12, &in16, &load);
            addr_bit12.value += 585;
            in16.value += 2;
            WriteRAM4k(&ram16k.ram2, &addr_bit12, &in16, &load);
            addr_bit12.value += 585;
            in16.value += 2;
            WriteRAM4k(&ram16k.ram3, &addr_bit12, &in16, &load);
        }
};

TEST_P(Ram16kRead, ComparesRam16kOutputWithValuesToExpected) {
    addr_bit14.value = std::get<0>(GetParam());
    exp_byte2.value = std::get<1>(GetParam());
    p_res_byte2 = ReadRAM16k(&ram16k, &addr_bit14);
    ASSERT_EQ(p_res_byte2->value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Ram16kReadWithValuesParameterized,
    Ram16kRead,
    testing::Values(
        std::make_tuple(0, 0),
        std::make_tuple(4681, 2),
        std::make_tuple(9362, 4),
        std::make_tuple(14043, 6)
    )
);

/* 
-------------------------------------------------------------------------------
                            RAM4k WRITE TESTS
-------------------------------------------------------------------------------
*/

class Ram16kWrite : public MemoryTest, 
                    public testing::WithParamInterface<std::tuple<int, int, int, int>> {
    protected:
        struct RAM16k ram16k = { 0 };
};

TEST_P(Ram16kWrite, ComparesRam16kWrittenOutputToExpected) {
    addr_bit14.value = std::get<0>(GetParam());
    in16.value = std::get<1>(GetParam());
    load.value = std::get<2>(GetParam());
    exp_byte2.value = std::get<3>(GetParam());
    WriteRAM16k(&ram16k, &addr_bit14, &in16, &load);
    p_res_byte2 = ReadRAM16k(&ram16k, &addr_bit14);
    ASSERT_EQ(p_res_byte2->value, exp_byte2.value);
}

INSTANTIATE_TEST_SUITE_P(
    Ram16kWriteParameterized,
    Ram16kWrite,
    testing::Values(
        std::make_tuple(0, 123, 0, 0),
        std::make_tuple(0, 123, 1, 123),
        std::make_tuple(4681, 456, 0, 0),
        std::make_tuple(4681, 456, 1, 456),
        std::make_tuple(9362, 789, 0, 0),
        std::make_tuple(9362, 789, 1, 789),
        std::make_tuple(14043, 123, 0, 0),
        std::make_tuple(14043, 123, 1, 123)
    )
);
