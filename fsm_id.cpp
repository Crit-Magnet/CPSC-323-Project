#include "fsm_id.h"

#include <cctype>  // Needed for isalpha() and isalnum()

bool FSMid(const std::string& lexeme) {
    int state = 1;  // Start in State 1

    for (char c : lexeme) {  // Iterate through each character in the string
        switch (state) {
            case 1:  // Start state
                if (isalpha(c) || c == '_')
                    state = 2;  // Valid first character (letter or underscore)
                else
                    return false;  // Invalid first character → not an identifier
                break;

            case 2:  // Valid identifier state
                if (isalnum(c) || c == '_')
                    continue;  // Keep processing valid identifier characters
                else
                    return false;  // Invalid character encountered → reject
                break;
        }
    }

    return state == 2;  // Accepting state: Valid identifier if ended in state 2
}
