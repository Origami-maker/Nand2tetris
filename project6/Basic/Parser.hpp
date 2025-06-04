#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

class Parser {
    public:
        // Enum for instruction types
        enum class InstructionType {
            A_INSTRUCTION,
            C_INSTRUCTION,
            L_INSTRUCTION,
            NO_INSTRUCTION
        };

    private:
        std::ifstream inputFile;
        std::string currentLine;
        std::string currentCommand;
        InstructionType currentInstructionType;
    
    public:
        // Constructor
        Parser(const std::string& FILE_NAME) : inputFile(FILE_NAME) {
            if(!inputFile) {
                std::cerr << "Error: Could not open file " << FILE_NAME << std::endl;
                throw std::runtime_error("File not found or could not be opened.");
            }
            if (inputFile.eof()) {
                std::cerr << "Error: File " << FILE_NAME << " is empty." << std::endl;
                throw std::runtime_error("File is empty.");
            }
        };

        bool hasMoreLines() {
            if (inputFile.eof()) {
                return false;
            }
            std::getline(inputFile, currentLine);
            return true;
        }

        void advance() {
            if (currentLine.empty()) {
                currentCommand = "";
                return; // No command to process
            }
            // Remove whitespace and comments
            size_t commentPos = currentLine.find("//");
            std::string noCommentLine = (commentPos != std::string::npos) ? currentLine.substr(0, commentPos) : currentLine;

            if (std::all_of(noCommentLine.begin(), noCommentLine.end(), [](unsigned char c) { return std::isspace(c); })) {
                currentCommand = ""; // If the line is only whitespace, set currentCommand to empty
                return;
            }
            auto it1 = noCommentLine.begin();
            while( it1 != noCommentLine.end() && std::isspace(static_cast<unsigned char>(*it1))) {
                ++it1;
            }

            auto it2 = noCommentLine.end();
            while (it2 != noCommentLine.begin() && std::isspace(static_cast<unsigned char>(*(it2 - 1)))) {
                --it2;
            }

            currentCommand = std::string(it1, it2);
        }

        InstructionType instructionType() {
            if (currentCommand.empty()) {
                std::cout << "No instructin found in the current line. skipping..." << std::endl;
                return InstructionType::NO_INSTRUCTION;
            }
            if (currentCommand[0] == '@') {
                currentInstructionType = InstructionType::A_INSTRUCTION;
                return InstructionType::A_INSTRUCTION;
            } else if (currentCommand[0] == '(' && currentCommand.back() == ')') {
                currentInstructionType = InstructionType::L_INSTRUCTION;
                return InstructionType::L_INSTRUCTION;
            } else {
                currentInstructionType = InstructionType::C_INSTRUCTION;
                return InstructionType::C_INSTRUCTION;
            }
        }

        std::string symbol() {
            if (currentInstructionType == InstructionType::A_INSTRUCTION) {
                return currentCommand.substr(1);
            }
            else if (currentInstructionType == InstructionType::L_INSTRUCTION) {
                return currentCommand.substr(1, currentCommand.size() - 2);
            } else {
                std::cerr << "Error: Current command is not an A or L instruction." << std::endl;
                throw std::runtime_error("Current command is not an A or L instruction.");
            }
        }

        std::string dest() {
            size_t eqPos = currentCommand.find('=');
            if (eqPos != std::string::npos) {
                return currentCommand.substr(0, eqPos);
            } else {
                return "null"; // No destination
            }

            if (currentInstructionType != InstructionType::C_INSTRUCTION) {
                std::cerr << "Error: Current command is not a C instruction." << std::endl;
                throw std::runtime_error("Current command is not a C instruction.");
            }
        }

        std::string comp() {
            size_t eqpos = currentCommand.find('=');
            if (eqpos != std::string::npos) {
                size_t semicolonPos = currentCommand.find(';', eqpos);
                if (semicolonPos != std::string::npos) {
                    return currentCommand.substr(eqpos + 1, semicolonPos - eqpos - 1);
                } else {
                    return currentCommand.substr(eqpos + 1);
                }
            }
            else {
                size_t semicolonPos = currentCommand.find(';');
                if (semicolonPos != std::string::npos) {
                    return currentCommand.substr(0, semicolonPos);
                } else {
                    return currentCommand;
                }
            }

            if (currentInstructionType != InstructionType::C_INSTRUCTION) {
                std::cerr << "Error: Current command is not a C instruction." << std::endl;
                throw std::runtime_error("Current command is not a C instruction.");
            }
        }

        std::string jump() {
            size_t semicolonPos = currentCommand.find(';');
            if (semicolonPos != std::string::npos) {
                return currentCommand.substr(semicolonPos + 1);
            } else {
                return "null"; // No jump
            }

            if (currentInstructionType != InstructionType::C_INSTRUCTION) {
                std::cerr << "Error: Current command is not a C instruction." << std::endl;
                throw std::runtime_error("Current command is not a C instruction.");
            }
        }
};