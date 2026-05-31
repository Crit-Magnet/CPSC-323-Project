#ifndef TOKEN_H
#define TOKEN_H

#include <string>

// Token structure to store type and lexeme
struct Token {
  std::string type;    // e.g., "keyword", "identifier", "operator"
  std::string lexeme;  // Actual text from source code
};

#endif  // TOKEN_H
