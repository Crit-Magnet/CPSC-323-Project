#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "lexer.h"

// Function prototype (assuming lexer is in a separate file)
std::vector<Token> lexer(const std::string &source_code);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
        return 1;
    }

    // Read file into a string
    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();  // Read entire file into buffer
    std::string source_code = buffer.str();  // Convert to string

    // Open output file for writing
    std::ofstream output_file("output.txt");
    if (!output_file) {
        std::cerr << "Error: Could not open output.txt for writing." << std::endl;
        return 1;
    }

    // Print input to file
    output_file << "===== INPUT =====" << std::endl;
    output_file << source_code << std::endl;

    // Tokenize the input
    std::vector<Token> tokens = lexer(source_code);

    // Print tokenized output to file
    output_file << "\n===== TOKENIZED OUTPUT =====" << std::endl;

    for (const auto &token : tokens) {
        output_file << "Token: " << token.type << ", Lexeme: " << token.lexeme << std::endl;
    }

    // Close the output file
    output_file.close();

    return 0;
}
