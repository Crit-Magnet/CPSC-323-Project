#ifndef SEPARATORS_H
#define SEPARATORS_H

#include <string>
#include <unordered_set>

// Set of valid separators
const std::unordered_set<std::string> separators = {";", ",", "(",  ")",
                                                    "{", "}", "$$", "$"};

#endif  // SEPARATORS_H
