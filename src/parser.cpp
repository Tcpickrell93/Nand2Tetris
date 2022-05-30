#include "machine_language_defines.h"

#include <string>
#include <iostream>
#include <fstream>

namespace Parser {

    void Parse(std::string file_path) {
        std::ifstream inFile(file_path);
        std::string current_line;
        instruction_type current_instruction_type;
        std::string current_symbol;
        std::string current_dest;
        std::string current_comp;
        std::string current_jump;

        while (inFile) {
            // Get current line
            std::getline(inFile, current_line);
            // Get instruction type
            current_instruction_type = Instruction_type(current_line);
            if (current_instruction_type == A_INSTRUCTION 
                || current_instruction_type == L_INSTRUCTION) {
                    // Get symbol
                    current_symbol = Symbol(current_line, current_instruction_type);
            }
            if (current_instruction_type == C_INSTRUCTION) {
                // Get Destination
                current_dest = Dest(current_line);
                // Get Computation
                current_comp = Comp(current_line);
                // Get Jump
                current_jump = Jump(current_line);
            }   
        }
    }

    instruction_type Instruction_type(const std::string line) {
        if (line.front() == '@') {
            return A_INSTRUCTION;
        }
        if (line.front() == '(') {
            return L_INSTRUCTION;
        }
        return C_INSTRUCTION;
    }

    std::string Symbol(const std::string line, 
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

    std::string Dest(const std::string line) {
        std::string dest { line };
        int equal_pos = dest.find('=');
        dest.erase(equal_pos, line.size() - equal_pos);
        return dest;
    }

    std::string Comp(const std::string line) {
        std::string comp { line };
        int equal_pos = comp.find('=');
        int semi_colon_pos = comp.find(';');
        comp.erase(0, equal_pos+1);
        return comp;
    }

    std::string Jump(const std::string line) {
        std::string jump { line };
        int semi_colon_pos = jump.find(';');
        if (semi_colon_pos == std::string::npos) {
            return "null";
        }
        jump.erase(0, semi_colon_pos+1);
        return jump;
    }

} // Parser
