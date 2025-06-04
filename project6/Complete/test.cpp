#include <iostream>
#include <string>
#include <algorithm>

std::string advance(std::string& input) {
    if (input.empty()) {
        return ""; // Return empty string if input is empty
    }

    size_t commentPos = input.find("//");
    std::string noCommentLine = (commentPos != std::string::npos) ? input.substr(0, commentPos) : input;

    if (std::all_of(noCommentLine.begin(), noCommentLine.end(), [](unsigned char c) { return std::isspace(c); })) {
        return ""; // Return empty string if the line is only whitespace
    }
    auto it1 = noCommentLine.begin();
    while (it1 != noCommentLine.end() && std::isspace(static_cast<unsigned char>(*it1))) {
        ++it1;
    }

    auto it2 = noCommentLine.end();
    while (it2 != noCommentLine.begin() && std::isspace(static_cast<unsigned char>(*(it2 - 1)))) {
        --it2;
    }

    auto output = std::string(it1, it2);
    return output;
}

int main() {
    std::string input = " ";
    std::string output = advance(input);
    if (output.empty()) {
        std::cout << "No valid command found." << std::endl;
    } else {
        std::cout << "Processed command: " << output << std::endl;
    }
    return 0;
}