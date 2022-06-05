
#include <string>
#include <map>


namespace Assembler {

    void Initialize_symbol_table(std::map<std::string, int>& symbol_table);
    void First_pass(const std::string in_file_path, 
                    std::map<std::string, int>& symbol_table);
    std::string Process_A_instruction(const std::string symbol,
                                      std::map<std::string, int>& symbol_table,
                                      int& current_available_address);
    std::string Process_C_instruction(const std::string dest,
                                      const std::string comp,
                                      const std::string jump);
    std::string Process_L_instruction(const std::string symbol, 
                                      std::map<std::string, int> symbol_table);
    void Second_pass(const std::string in_file_path, 
                    std::map<std::string, int>& symbol_table);
    void Assemble(const std::string in_file_path);

} // Assembler