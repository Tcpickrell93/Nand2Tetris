#include "parser.h"
#include "machine_language_defines.h"

#include <string>
#include <iostream>
#include <fstream>


Parser::Parser(const std::string file_path) : ifs_ { file_path }
{
}

bool Parser::Has_more_lines() {
    //std::cout << ifs_.peek() << std::endl;
    if (ifs_.peek() == EOF) { return false; }
    return true;
}

std::string Parser::Advance() {
    std::string next_line;
    std::getline(ifs_, next_line);
    return next_line;
}

instruction_type Parser::Instruction_type(const std::string line) {
    if (line.front() == '@') {
        return A_INSTRUCTION;
    }
    if (line.front() == '(') {
        return L_INSTRUCTION;
    }
    return C_INSTRUCTION;
}

std::string Parser::Symbol(const std::string line, 
                           const instruction_type instruction) {
    std::string symbol { line };
    if (instruction == A_INSTRUCTION) {
        symbol.erase(0, 1);
    }
    if (instruction == L_INSTRUCTION) {
        int line_size = line.size();
        symbol.erase(line_size-1, 1);
        symbol.erase(0, 1);
    }
    return symbol;
}

std::string Parser::Dest(const std::string line) {
    std::string dest { line };
    int equal_pos = dest.find('=');
    dest.erase(equal_pos, line.size() - equal_pos);
    return dest;
}

std::string Parser::Comp(const std::string line) {
    std::string comp { line };
    int semi_colon_pos = comp.find(';');
    if (semi_colon_pos != std::string::npos) {
        comp.erase(semi_colon_pos, comp.size()-semi_colon_pos);
    }
    int equal_pos = comp.find('=');
    comp.erase(0, equal_pos+1);
    return comp;
}

std::string Parser::Jump(const std::string line) {
    std::string jump { line };
    int semi_colon_pos = jump.find(';');
    if (semi_colon_pos == std::string::npos) {
        return "null";
    }
    jump.erase(0, semi_colon_pos+1);
    return jump;
}