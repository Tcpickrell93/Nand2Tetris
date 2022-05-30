#include "machine_language_defines.h"
#include "bits.h"   

#include <string>
#include <iostream>
#include <fstream>

namespace Code_gen {

    byte2 Dest(std::string dest) {
        if (dest == "null") { return D_NULL; }
        if (dest == "M")    { return D_M; }
        if (dest == "D")    { return D_D; }
        if (dest == "DM")   { return D_DM; }
        if (dest == "A")    { return D_A; }
        if (dest == "AM")   { return D_AM; }
        if (dest == "AD")   { return D_AD; }
        if (dest == "ADM")  { return D_ADM; }
        std::cout << "DESTINATION NOT FOUND" << std::endl;
        return D_NULL;
    }

    byte2 Comp(std::string comp) {
        if (comp == "0")    { return C_0; }
        if (comp == "1")    { return C_1; }
        if (comp == "-1")   { return C_NEG_1; }
        if (comp == "D")    { return C_D; }
        if (comp == "A")    { return C_A; }
        if (comp == "!D")   { return C_NOT_D; }
        if (comp == "!A")   { return C_NOT_A; }
        if (comp == "-D")   { return C_NEG_D; }
        if (comp == "-A")   { return C_NEG_A; }
        if (comp == "D+1")  { return C_D_PLUS_1; }
        if (comp == "A+1")  { return C_A_PLUS_1; }
        if (comp == "D-1")  { return C_D_MINUS_1; }
        if (comp == "A-1")  { return C_A_MINUS_1; }
        if (comp == "D+A")  { return C_D_PLUS_A; }
        if (comp == "D-A")  { return C_D_MINUS_A; }
        if (comp == "A-D")  { return C_A_MINUS_D; }
        if (comp == "D&A")  { return C_D_AND_A; }
        if (comp == "D|A")  { return C_D_OR_A; }
        if (comp == "M")    { return C_M; }
        if (comp == "!M")   { return C_NOT_M; }
        if (comp == "-M")   { return C_NEG_M; }
        if (comp == "M+1")  { return C_M_PLUS_1; }
        if (comp == "M-1")  { return C_M_MINUS_1; }
        if (comp == "D+M")  { return C_D_PLUS_M; }
        if (comp == "D-M")  { return C_D_MINUS_M; }
        if (comp == "M-D")  { return C_M_MINUS_D; }
        if (comp == "D&M")  { return C_D_AND_M; }
        if (comp == "D|M")  { return C_D_OR_M; }
        std::cout << "COMPUTATION NOT FOUND" << std::endl;
        return C_0;
    }

    byte2 Jump(std::string jump) {
        if (jump == "null") { return J_NULL; }
        if (jump == "JGT")  { return J_JGT; }
        if (jump == "JEQ")  { return J_JEQ; }
        if (jump == "JGE")  { return J_JGE; }
        if (jump == "JLT")  { return J_JLT; }
        if (jump == "JNE")  { return J_JNE; }
        if (jump == "JLE")  { return J_JLE; }
        if (jump == "JMP")  { return J_JMP; }
        std::cout << "JUMP NOT FOUND" << std::endl;
        return J_NULL;
    }

} // Code_gen