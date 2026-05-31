#include "lexer.h"

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "fsm_id.h"      // Identifiers FSM
#include "fsm_number.h"  // Numbers FSM
#include "keywords.h"    // List of keywords
#include "operators.h"   // List of operators
#include "separators.h"  // List of separators

std::vector<Token> lexer(const std::string &source_code) {
  std::vector<Token> tokens;
  size_t i = 0;

  while (i < source_code.size()) {
    char ch = source_code[i];

    // 1) Skip Whitespace
    if (isspace(ch)) {
      i++;
      continue;
    }

    // 2) Skip Comments [* ... *]
    //    If we see '[' followed by '*', skip until '*]'
    if (ch == '[' && (i + 1 < source_code.size()) &&
        source_code[i + 1] == '*') {
      i += 2;  // Skip "[*"
      // Advance until we find "*]" or reach end
      while (i + 1 < source_code.size() &&
             !(source_code[i] == '*' && source_code[i + 1] == ']')) {
        i++;
      }
      i += 2;  // Skip the closing "*]"
      continue;
    }

    // 3) Check Separators
    //    First look for a two-character separator (e.g., "$$"), then check
    //    one-character separators
    std::string sep1(1, source_code[i]);  // Wrap current character as string
    std::string sep2;
    if (i + 1 < source_code.size()) {
      sep2 = sep1 +
             source_code[i + 1];  // Create a potential 2-character separator
    }

    // Check if sep2 (e.g., "$$") is a valid multi-character separator
    if (!sep2.empty() && separators.find(sep2) != separators.end()) {
      tokens.push_back(
          {"separator", sep2});  // Found a valid 2-character separator
      i += 2;
      continue;
    }

    // Check for single-character separator (e.g., ";", "}", etc.)
    if (separators.find(sep1) != separators.end()) {
      tokens.push_back({"separator", sep1});
      i++;
      continue;
    }

    // 4) Check Operators (multi-char first, e.g. ==, !=, <=, =>)
    //    Then single-char (e.g. +, -, /, *)
    std::string op1(1, ch);
    std::string op2;
    if (i + 1 < source_code.size()) {
      op2 = op1 + source_code[i + 1];
    }

    // Check two-character operator
    if (operators.find(op2) != operators.end()) {
      tokens.push_back({"operator", op2});
      i += 2;
      continue;
    }
    // Check single-character operator
    else if (operators.find(op1) != operators.end()) {
      tokens.push_back({"operator", op1});
      i++;
      continue;
    }

    // 5) Unified Chunk Approach:
    //    Collect all consecutive non-whitespace, non-comment, non-operator,
    //    non-separator characters into one 'chunk'.
    std::string chunk;
    while (i < source_code.size()) {
      // Check if next char starts whitespace
      if (isspace(source_code[i])) break;

      // Check if next char starts a comment [* ... *]
      if (source_code[i] == '[' && (i + 1 < source_code.size()) &&
          source_code[i + 1] == '*') {
        break;
      }

      // Check next char(s) for operator
      std::string peek1(1, source_code[i]);
      std::string peek2;
      if (i + 1 < source_code.size()) {
        peek2 = peek1 + source_code[i + 1];
      }
      if (operators.find(peek2) != operators.end()) break;
      if (operators.find(peek1) != operators.end()) break;

      // Check if next char is a separator
      if (separators.find(peek1) != separators.end()) break;

      // If none of the above, append to chunk
      chunk.push_back(source_code[i]);
      i++;
    }

    // If chunk is empty (unlikely here), we skip
    if (chunk.empty()) {
      // If we get here, it's probably an unknown single char
      tokens.push_back({"INVALID", std::string(1, ch)});
      i++;
      continue;
    }

    // 6) Classify the chunk
    //  - Keyword?
    //  - Identifier (FSMid)?
    //  - Number (FSMnum)? -> integer or real
    //  - Otherwise INVALID
    if (keywords.find(chunk) != keywords.end()) {
      tokens.push_back({"keyword", chunk});
    } else if (FSMid(chunk)) {
      tokens.push_back({"identifier", chunk});
    } else if (FSMnum(chunk)) {
      // Distinguish integer vs real by checking for '.'
      if (chunk.find('.') != std::string::npos) {
        tokens.push_back({"real", chunk});
      } else {
        tokens.push_back({"integer", chunk});
      }
    } else {
      tokens.push_back({"INVALID", chunk});
    }
  }

  return tokens;
}