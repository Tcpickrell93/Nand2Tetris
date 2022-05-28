#ifndef ADD_H
#define ADD_H

#include "machine_language_defines.h"

byte2 Add_2_and_3_program[4] {
    0b0000'0000'0000'0010u,     // Set A to 2
    C_A|D_D|J_NULL,             // Set D to A
    0b0000'0000'0000'0011u,     // Set A to 3
    C_D_PLUS_A|D_M|J_NULL       // Set M to A plus D
}

#endif // ADD_H