#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

class SymbolTable {
    private:
        std::unordered_map<std::string, int> symbolTable;
        int nextAvailableAddress = 16; // Starting address for user-defined symbols

    public:
        SymbolTable():
            // Pre-defined symbols
            symbolTable({
                {"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3},
                {"R4", 4}, {"R5", 5}, {"R6", 6}, {"R7", 7},
                {"R8", 8}, {"R9", 9}, {"R10", 10}, {"R11", 11},
                {"R12", 12}, {"R13", 13}, {"R14", 14}, {"R15", 15},
                {"SCREEN", 16384}, {"KBD", 24576},
                {"SP", 0}, {"LCL", 1}, {"ARG", 2}, {"THIS", 3},
                {"THAT", 4}
            }) {};

        void addLabelEntry(std::string& symbol, const int& address) {
            if (symbolTable.find(symbol) == symbolTable.end()) {
                symbolTable[symbol] = address;
            }
        }

        void addSymbolEntry(std::string& symbol) {
            if (symbolTable.find(symbol) == symbolTable.end()) {
                symbolTable[symbol] = nextAvailableAddress++;
            }
        }

        bool contains(std::string& symbol) {
            return symbolTable.find(symbol) != symbolTable.end();
        }

        int getAddress(std::string& symbol) {
            if (contains(symbol)) {
                return symbolTable[symbol];
            } else {
                std::cerr << "Error: Symbol '" << symbol << "' not found in the symbol table." << std::endl;
                throw std::runtime_error("Symbol not found.");
            }
        }
};
