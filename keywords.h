#ifndef KEYWORDS_H
#define KEYWORDS_H

#include <string>
#include <unordered_set>

// Set of reserved keywords for quick lookup
const std::unordered_set<std::string> keywords = {
    "function", "integer", "boolean", "real", "if",    "endif",
    "else",     "return",  "print",   "scan", "while", "endwhile"};

#endif  // KEYWORDS_H
