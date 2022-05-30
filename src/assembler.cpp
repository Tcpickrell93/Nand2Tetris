#include "parser.h"
#include "code_gen.h"

#include <string>
#include <map>
#include <iostream>
#include <fstream>

namespace Assembly {

    void Initialize_symbol_table(std::map<std::string, int>& symbol_table) {
        symbol_table["R0"] =        0;
        symbol_table["R1"] =        1;
        symbol_table["R2"] =        2;
        symbol_table["R3"] =        3;
        symbol_table["R4"] =        4;
        symbol_table["R5"] =        5;
        symbol_table["R6"] =        6;
        symbol_table["R7"] =        7;
        symbol_table["R8"] =        8;
        symbol_table["R9"] =        9;
        symbol_table["R10"] =       10;
        symbol_table["R11"] =       11;
        symbol_table["R12"] =       12;
        symbol_table["R13"] =       13;
        symbol_table["R14"] =       14;
        symbol_table["R15"] =       15;
        symbol_table["SCREEN"] =    16384;
        symbol_table["KBD"] =       24576;
        symbol_table["SP"] =        0;
        symbol_table["LCL"] =       1;
        symbol_table["ARG"] =       2;
        symbol_table["THIS"] =      3;
        symbol_table["THAT"] =      4;
    }

    void First_pass(const std::string in_file_path, 
                    std::map<std::string, int>& symbol_table) {
        // Create Parser
        Parser parser = Parser(in_file_path);
        // Line of input file we are currently processing
        std::string current_line;
        int line_num { 0 };
        // Instruction type of current line
        instruction_type current_instruction_type;
        // Symbol in line if it exists
        std::string current_symbol;

        while (parser.Has_more_lines()) {
            // Get current line
            current_line = parser.Advance();
            // Get instruction type
            current_instruction_type = parser.Instruction_type(current_line);
            // Only checking label instructions for first pass
            if (current_instruction_type != L_INSTRUCTION) {
                continue;
            }
            current_symbol = parser.Symbol(current_line, current_instruction_type);
            symbol_table[current_symbol] = line_num++;
        }
    }

    std::string Process_A_instruction(const std::string symbol,
                                    std::map<std::string, int>& symbol_table,
                                    int& current_available_address) {
        // Check if symbol is an integer
        bool is_integer { true };
        for (int i = 0; i < symbol.size(); i++) {
            if (!std::isdigit(symbol[i])) {
                is_integer = false;
            }
        }
        // Handle when symbol is an integer
        if (is_integer) {
            byte2 binary_address { std::stoi(symbol) };
            return binary_address.to_string();
        }
        // Symbol is a variable
        if (symbol_table.find(symbol) == symbol_table.end()) {
            symbol_table[symbol] = current_available_address;
            byte2 binary_address { current_available_address };
            current_available_address++;
            return binary_address.to_string();
        } else {
            byte2 binary_address { symbol_table[symbol] };
            return binary_address.to_string();
        }
    }

    std::string Process_C_instruction(const std::string dest,
                                    const std::string comp,
                                    const std::string jump) {
        byte2 instruction { Code_gen::Dest(dest) | Code_gen::Comp(comp) | Code_gen::Jump(jump) };
        return instruction.to_string();
    }

    std::string Process_L_instruction(const std::string symbol, 
                                    std::map<std::string, int> symbol_table) {
        byte2 instruction { symbol_table[symbol] };
        return instruction.to_string();
    }

    void Second_pass(const std::string in_file_path, 
                    std::map<std::string, int>& symbol_table) {
        // Open output file
        std::string out_file_path { in_file_path };
        int ext_pos { out_file_path.find('.') };
        out_file_path.erase(ext_pos, out_file_path.size()-ext_pos);
        std::ofstream outfile;
        outfile.open(out_file_path);
        // Create Parser
        Parser parser = Parser(in_file_path);
        // Line of input file we are currently processing
        std::string current_line;
        // Instruction type of current line
        instruction_type current_instruction_type;
        // Symbol in line if it exists
        std::string current_symbol;
        // Destination in line if it exists
        std::string current_dest;
        // Computation in line if it exists
        std::string current_comp;
        // Jump in line if it exists
        std::string current_jump;
        // Current address to assign to next variable
        int current_available_address { 16 };

        while (parser.Has_more_lines()) {
            // Get current line
            current_line = parser.Advance();
            // Get instruction type
            current_instruction_type = parser.Instruction_type(current_line);
            // Process instruction based on type
            switch (current_instruction_type) {
                case A_INSTRUCTION:
                    current_symbol = parser.Symbol(current_line, current_instruction_type);
                    outfile << Assembly::Process_A_instruction(current_symbol, symbol_table, current_available_address) << std::endl;
                
                case L_INSTRUCTION:
                    current_symbol = parser.Symbol(current_line, current_instruction_type);
                    outfile << Assembly::Process_L_instruction(current_symbol, symbol_table) << std::endl;

                case C_INSTRUCTION:
                    current_dest = parser.Dest(current_line);
                    current_comp = parser.Comp(current_line);
                    current_jump = parser.Jump(current_line);
                    outfile << Assembly::Process_C_instruction(current_dest, current_comp, current_jump) << std::endl;
            } 
        }
        outfile.close();
    }

    void Assemble(const std::string in_file_path) {
        // Create Symbol Table
        std::map<std::string, int> symbol_table;
        Initialize_symbol_table(symbol_table);
        // Run first pass
        First_pass(in_file_path, symbol_table);
        // Run second pass
        Second_pass(in_file_path, symbol_table);
    }

} // Assembly