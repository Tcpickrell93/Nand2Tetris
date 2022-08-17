#ifndef MACHINE_LANGUAGE_DEFINES
#define MACHINE_LANGUAGE_DEFINES

#include "bits.h"   

enum instruction_type {
    A_INSTRUCTION,
    C_INSTRUCTION,
    L_INSTRUCTION
};

//                                                     111'a'cccccc'dddjjj
union byte2_u C_0 = { .value = 60032 };             // 111'0'101010'000000
union byte2_u C_1 = { .value = 61376 };             // 111'0'111111'000000
union byte2_u C_NEG_1 = { .value = 61056 };         // 111'0'111010'000000
union byte2_u C_D = { .value = 58112 };             // 111'0'001100'000000
union byte2_u C_A = { .value = 60416 };             // 111'0'110000'000000
union byte2_u C_NOT_D = { .value = 58176 };         // 111'0'001101'000000
union byte2_u C_NOT_A = { .value = 60480 };         // 111'0'110001'000000
union byte2_u C_NEG_D = { .value = 58304 };         // 111'0'001111'000000
union byte2_u C_NEG_A = { .value = 60608 };         // 111'0'110011'000000
union byte2_u C_D_PLUS_1 = { .value = 59328 };      // 111'0'011111'000000
union byte2_u C_A_PLUS_1 = { .value = 60864 };      // 111'0'110111'000000
union byte2_u C_D_MINUS_1 = { .value = 58240 };     // 111'0'001110'000000
union byte2_u C_A_MINUS_1 = { .value = 60544 };     // 111'0'110010'000000
union byte2_u C_D_PLUS_A = { .value = 57472 };      // 111'0'000010'000000
union byte2_u C_D_MINUS_A = { .value = 58560 };     // 111'0'010011'000000
union byte2_u C_A_MINUS_D = { .value = 57792 };     // 111'0'000111'000000
union byte2_u C_D_AND_A = { .value = 57344 };       // 111'0'000000'000000
union byte2_u C_D_OR_A = { .value = 58688 };        // 111'0'010101'000000
union byte2_u C_M = { .value = 64512 };             // 111'1'110000'000000
union byte2_u C_NOT_M = { .value = 64576 };         // 111'1'110001'000000
union byte2_u C_NEG_M = { .value = 64704 };         // 111'1'110011'000000
union byte2_u C_M_PLUS_1 = { .value = 64960 };      // 111'1'110111'000000
union byte2_u C_M_MINUS_1 = { .value = 64640 };     // 111'1'110010'000000
union byte2_u C_D_PLUS_M = { .value = 61568 };      // 111'1'000010'000000
union byte2_u C_D_MINUS_M = { .value = 62656 };     // 111'1'010011'000000
union byte2_u C_M_MINUS_D = { .value = 61888 };     // 111'1'000111'000000
union byte2_u C_D_AND_M = { .value = 61440 };       // 111'1'000000'000000
union byte2_u C_D_OR_M = { .value = 62784 };        // 111'1'010101'000000

union byte2_u D_NULL = { .value = 57344 };          // 111'0'000000'000000
union byte2_u D_M = { .value = 57352 };             // 111'0'000000'001000
union byte2_u D_D = { .value = 57360 };             // 111'0'000000'010000
union byte2_u D_DM = { .value = 57368 };            // 111'0'000000'011000
union byte2_u D_A = { .value = 57376 };             // 111'0'000000'100000
union byte2_u D_AM = { .value = 57384 };            // 111'0'000000'101000
union byte2_u D_AD = { .value = 57392 };            // 111'0'000000'110000
union byte2_u D_ADM = { .value = 57400 };           // 111'0'000000'111000

union byte2_u J_NULL = { .value = 57344 };          // 111'0'000000'000000
union byte2_u J_JGT = { .value = 57345 };           // 111'0'000000'000001
union byte2_u J_JEQ = { .value = 57346 };           // 111'0'000000'000010
union byte2_u J_JGE = { .value = 57347 };           // 111'0'000000'000011
union byte2_u J_JLT = { .value = 57348 };           // 111'0'000000'000100
union byte2_u J_JNE = { .value = 57349 };           // 111'0'000000'000101
union byte2_u J_JLE = { .value = 57350 };           // 111'0'000000'000110
union byte2_u J_JMP = { .value = 57351 };           // 111'0'000000'000111

#endif // MACHINE_LANGUAGE_DEFINES

