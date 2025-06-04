#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <bitset>
#include "Parser.hpp"
#include "Code.hpp"
#include "SymbolTable.hpp"

// Helper function
bool isNumber(const std::string& symbol) {
    return !symbol.empty() && std::all_of(symbol.begin(), symbol.end(), [&](unsigned char c) { return std::isdigit(c); });
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file.asm>" << std::endl;
        throw std::invalid_argument("Invalid number of arguments. Expected 1 argument: input file name.");
    }
    std::string inputFileName = argv[1];
    std::string outputFileName = inputFileName.substr(0, inputFileName.find_last_of('.')) + ".hack";
    std::ofstream outputFile(outputFileName);

    // 1st pass : Label Symbol definition
    SymbolTable symbolTable;
    Parser parser1(inputFileName);
    while(parser1.hasMoreLines()) {
        parser1.advance();
        auto instructionType = parser1.instructionType();
        if (instructionType == Parser::InstructionType::NO_INSTRUCTION) {
            continue; // Skip empty lines or comments
        }
        
        if (instructionType == Parser::InstructionType::L_INSTRUCTION) {
            std::string symbol = parser1.symbol();
            if (!symbolTable.contains(symbol)) {
                symbolTable.addLabelEntry(symbol, parser1.getCurrentLineNumber()+1); // +1 because we want to store the line number of the next instruction
            } else {
                std::cerr << "Warning: Label '" << symbol << "' already defined at line " 
                          << parser1.getCurrentLineNumber() << ". Skipping duplicate definition." << std::endl;
            }
            
        }
    }
    
    // 2nd pass : Symbol table
    Parser parser2(inputFileName);
    while (parser2.hasMoreLines()) {
        parser2.advance();
        auto instructionType = parser2.instructionType();
        if (instructionType == Parser::InstructionType::NO_INSTRUCTION) {
            continue; // Skip empty lines or comments
        }
        
        if (instructionType == Parser::InstructionType::A_INSTRUCTION) {
            std::string symbol = parser2.symbol();
            if (!isNumber(symbol) && !symbolTable.contains(symbol)) {
                symbolTable.addSymbolEntry(symbol);
            }
        }
    }

    // 3rd pass : Generate machine code
    Parser parser3(inputFileName);
    while (parser3.hasMoreLines()) {
        parser3.advance();
        auto instructionType = parser3.instructionType();
        if (instructionType == Parser::InstructionType::NO_INSTRUCTION) {
            continue; // Skip empty lines or comments
        }
        
        if (instructionType == Parser::InstructionType::A_INSTRUCTION) {
            std::string symbol = parser3.symbol();
            std::bitset<15> address;
            if (!isNumber(symbol)) {
                if (symbolTable.contains(symbol)) {
                    address = std::bitset<15>(symbolTable.getAddress(symbol));
                }
                else {
                    std::cerr << "Error: Symbol '" << symbol << "' not found in the symbol table." << std::endl;
                    throw std::runtime_error("Symbol not found.");  
                }
            } else {
                // if it is a number, convert it to an integer
                address = std::bitset<15>(std::stoi(symbol));
            }
            outputFile << "0" << address.to_string() << std::endl;
        }
        else if (instructionType == Parser::InstructionType::C_INSTRUCTION) {
            std::string dest = parser3.dest();
            std::string comp = parser3.comp();
            std::string jump = parser3.jump();

            std::string destBinary = Code::dest(dest);
            std::string compBinary = Code::comp(comp);
            std::string jumpBinary = Code::jump(jump);

            outputFile << "111" << compBinary << destBinary << jumpBinary << std::endl;
        }
        else if (instructionType == Parser::InstructionType::L_INSTRUCTION) {
            continue; // Skip label instructions
        }
        else {
            std::cerr << "Error: Unknown instruction type." << std::endl;
            throw std::runtime_error("Unknown instruction type.");
        }
    }
    outputFile.close();
    std::cout << "Assembly completed. Output written to " << outputFileName << std::endl;
    return 0;
}