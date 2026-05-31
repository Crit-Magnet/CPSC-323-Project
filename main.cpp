#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "SyntaxAnalyzer.h"
#include "lexer.h"

int main(int argc, char *argv[]) {
  // Check for input file argument
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
    return 1;
  }

  // Open source file
  std::ifstream file(argv[1]);
  if (!file) {
    std::cerr << "Error: Could not open file " << argv[1] << std::endl;
    return 1;
  }

  // Read entire file contents into a string
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string source_code = buffer.str();

  // Open output file for results
  std::ofstream output_file("output.txt");
  if (!output_file) {
    std::cerr << "Error: Could not open output.txt for writing." << std::endl;
    return 1;
  }

  // Write the input source code to the output file
  output_file << "===== INPUT =====\n" << source_code << "\n";

  // Tokenize input
  std::vector<Token> tokens = lexer(source_code); 

  // Run syntax analyzer on source code
  output_file << "\n===== SYNTAX ANALYSIS =====\n";
  SyntaxAnalyzer analyzer;
  analyzer.analyze(source_code, output_file);

  // Clean up
  output_file.close();
  return 0;
}
