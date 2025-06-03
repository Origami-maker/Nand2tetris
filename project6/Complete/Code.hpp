#include <string>
#include <iostream>

namespace Code {
    std::string dest(std::string destCode) {
        if (destCode == "null") return "000";
        else if (destCode == "M") return "001";
        else if (destCode == "D") return "010";
        else if (destCode == "DM" or destCode == "MD") return "011";
        else if (destCode == "A") return "100";
        else if (destCode == "AM") return "101";
        else if (destCode == "AD") return "110";
        else if (destCode == "ADM") return "111";
        else {
            std::cerr << "Error: Invalid dest code '" << destCode << "'." << std::endl;
            throw std::runtime_error("Invalid dest code.");
        }
    }

    std::string comp(std::string compCode) {
        if (compCode == "0") return "0101010";
        else if (compCode == "1") return "0111111";
        else if (compCode == "-1") return "0111010";
        else if (compCode == "D") return "0001100";
        else if (compCode == "A") return "0110000";
        else if (compCode == "M") return "1110000";
        else if (compCode == "!D") return "0001101";
        else if (compCode == "!A") return "0110001";
        else if (compCode == "!M") return "1110001";
        else if (compCode == "-D") return "0001111";
        else if (compCode == "-A") return "0110011";
        else if (compCode == "-M") return "1110011";
        else if (compCode == "D+1") return "0011111";
        else if (compCode == "A+1") return "0110111";
        else if (compCode == "M+1") return "1110111";
        else if (compCode == "D-1") return "0001110";
        else if (compCode == "A-1") return "0110010";
        else if (compCode == "M-1") return "1110010";
        else if (compCode == "D+A") return "0000010";
        else if (compCode == "D+M") return "1000010";
        else if (compCode == "D-A") return "0010011";
        else if (compCode == "D-M") return "1010011";
        else if (compCode == "A-D") return "0000111";
        else if (compCode == "M-D") return "1000111";
        else if (compCode == "D&A") return "0000000";
        else if (compCode == "D&M") return "1000000";
        else if (compCode == "D|A") return "0010101";
        else if (compCode == "D|M") return "1010101";
        else {
            std::cerr << "Error: Invalid comp code '" << compCode << "'." << std::endl;
            throw std::runtime_error("Invalid comp code.");
        }
    }

    std::string jump(std::string jumpCode) {
        if (jumpCode == "null") return "000";
        else if (jumpCode == "JGT") return "001";
        else if (jumpCode == "JEQ") return "010";
        else if (jumpCode == "JGE") return "011";
        else if (jumpCode == "JLT") return "100";
        else if (jumpCode == "JNE") return "101";
        else if (jumpCode == "JLE") return "110";
        else if (jumpCode == "JMP") return "111";
        else {
            std::cerr << "Error: Invalid jump code '" << jumpCode << "'." << std::endl;
            throw std::runtime_error("Invalid jump code.");
        }
    }
}