#include "machine_language_defines.h"

#include <string>
#include <iostream>
#include <fstream>


class Parser {
public:
    Parser(const std::string file_path);
    bool HasMoreLines();
    std::string Advance();
    instruction_type Instruction_type(const std::string line);
    std::string Symbol(const std::string line, 
                       const instruction_type instruction);
    std::string Dest(const std::string line);
    std::string Comp(const std::string line);
    std::string Jump(const std::string line);

private:
    std::ifstream ifs_;
};