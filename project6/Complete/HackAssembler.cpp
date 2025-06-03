#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include "Parser.hpp"
#include "Code.hpp"
#include "SymbolTable.hpp"


int main(int argc, char* argv[]) {
    std::string inputFileName = argv[1];
    std::string outputFileName = inputFileName.substr(0, inputFileName.find_last_of('.')) + ".hack";
    std::ofstream outputFile(outputFileName);

    // 1st pass : Symbol Table Population
    SymbolTable symbolTable;
    Parser parser1(inputFileName);
    while(parser1.hasMoreLines()) {
        parser1.advance();
        
    }

    // 2nd pass : Code Generation
    Parser parser2(inputFileName);
    while (parser2.hasMoreLines()) {
        parser2.advance();
        auto instructionType = parser2.instructionType();
        if (instructionType == Parser::InstructionType::NO_INSTRUCTION) {
            continue; // Skip empty lines or comments
        }
        
        if (instructionType == Parser::InstructionType::A_INSTRUCTION) {
            std::string symbol = parser2.symbol();
            std::bitset<15> address = std::bitset<15>(std::stoi(symbol));
            outputFile << "0" << address.to_string() << std::endl;
        }
        else if (instructionType == Parser::InstructionType::C_INSTRUCTION) {
            std::string dest = parser2.dest();
            std::string comp = parser2.comp();
            std::string jump = parser2.jump();

            std::string destBinary = Code::dest(dest);
            std::string compBinary = Code::comp(comp);
            std::string jumpBinary = Code::jump(jump);

            outputFile << "111" << compBinary << destBinary << jumpBinary << std::endl;
        }
        else if (instructionType == Parser::InstructionType::L_INSTRUCTION) {
            std::cerr << "Error: L instructions are not supported in this assembler." << std::endl;
            throw std::runtime_error("L instructions are not supported in this assembler.");
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