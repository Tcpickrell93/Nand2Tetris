#ifndef MACHINE_LANGUAGE_DEFINES
#define MACHINE_LANGUAGE_DEFINES

#include "bits.h"   

//                    111'a'cccccc'dddjjj
#define C_0         0b111'0'101010'000000u
#define C_1         0b111'0'111111'000000u
#define C_NEG_1     0b111'0'111010'000000u
#define C_D         0b111'0'001100'000000u
#define C_A         0b111'0'110000'000000u
#define C_NOT_D     0b111'0'001101'000000u
#define C_NOT_A     0b111'0'110001'000000u
#define C_NEG_D     0b111'0'001111'000000u
#define C_NEG_A     0b111'0'110011'000000u
#define C_D_PLUS_1  0b111'0'011111'000000u
#define C_A_PLUS_1  0b111'0'110111'000000u
#define C_D_MINUS_1 0b111'0'001110'000000u
#define C_A_MINUS_1 0b111'0'110010'000000u
#define C_D_PLUS_A  0b111'0'000010'000000u
#define C_D_MINUS_A 0b111'0'010011'000000u
#define C_A_MINUS_D 0b111'0'000111'000000u
#define C_D_AND_A   0b111'0'000000'000000u
#define C_D_OR_A    0b111'0'010101'000000u
#define C_M         0b111'1'110000'000000u
#define C_NOT_M     0b111'1'110001'000000u
#define C_NEG_M     0b111'1'110011'000000u
#define C_M_MINUS_1 0b111'1'110010'000000u
#define C_D_PLUS_M  0b111'1'000010'000000u
#define C_D_MINUS_M 0b111'1'010011'000000u
#define C_M_MINUS_D 0b111'1'000111'000000u
#define C_D_AND_M   0b111'1'000000'000000u
#define C_D_OR_M    0b111'1'010101'000000u

#define D_NULL      0b111'0'000000'000000u
#define D_M         0b111'0'000000'001000u
#define D_D         0b111'0'000000'010000u
#define D_DM        0b111'0'000000'011000u
#define D_A         0b111'0'000000'100000u
#define D_AM        0b111'0'000000'101000u
#define D_AD        0b111'0'000000'110000u
#define D_ADM       0b111'0'000000'111000u

#define J_NULL      0b111'0'000000'000000u
#define J_JGT       0b111'0'000000'000001u
#define J_JEQ       0b111'0'000000'000010u
#define J_JGE       0b111'0'000000'000011u
#define J_JLT       0b111'0'000000'000100u
#define J_JNE       0b111'0'000000'000101u
#define J_JLE       0b111'0'000000'000110u
#define J_JMP       0b111'0'000000'000111u

#endif // MACHINE_LANGUAGE_DEFINES

