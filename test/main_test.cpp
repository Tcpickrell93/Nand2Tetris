#include "logic_gates_test.h"
#include "arithmetic_chips_test.h"
#include "memory_test.h"
#include "program_counter_test.h"
#include "cpu_test.h"

#include <gtest/gtest.h>

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
