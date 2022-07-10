#include "logic_gates_test.h"
//#include "arithmetic_chips_test.h"
//#include "memory_test.h"
//#include "program_counter_test.h"
//#include "cpu_test.h"
//#include "computer_test.h"
//#include "parser_test.h"
//#include "assembler_test.h"
#include "../src/bits.h"

#include <gtest/gtest.h>

int main() {
    testing::InitGoogleTest();

    int test_result = RUN_ALL_TESTS();

    //printf("size of bit_2_s is %lu\n", sizeof(struct bit_2_s));
    //printf("size of bit_2_u is %lu\n", sizeof(union bit_2_u));

    return test_result;
}
