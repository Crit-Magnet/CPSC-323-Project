#ifndef LEXER_H
#define LEXER_H

#include <fstream>
#include <string>
#include <vector>

#include "token.h"

// Function to tokenize a string
std::vector<Token> lexer(const std::string &source_code);

// Function to tokenize a file
std::vector<Token> lexer(std::ifstream &file);

#endif  // LEXER_H