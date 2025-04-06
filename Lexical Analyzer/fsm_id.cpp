#include "../Lexical Analyzer/fsm_id.h"

#include <cctype>  // Needed for isalpha() and isdigit()
#include <string>

bool FSMid(const std::string& lexeme) {
    int state = 1;  // Start at state 1 (q0)

    for (char c : lexeme) {  // Iterate through each character in the input string
        switch (state) {
            case 1: // Start state (q0)
                if (isalpha(c)) state = 2;  // Letter -> Go to state 2
                else if (isdigit(c)) state = 5; // Digit -> Go to rejection state
                else return false;  // Invalid input
                break;

            case 2: // Valid identifier, second character
                if (isalpha(c)) state = 3;  // Letter -> Go to state 3
                else if (isdigit(c)) state = 4;  // Digit -> Go to state 4
                else return false;  // Invalid input
                break;

            case 3: // Continuing identifier state
                if (isalpha(c)) state = 3;  // Letter -> Stay in state 3
                else if (isdigit(c)) state = 4;  // Digit -> Move to state 4
                else return false;  // Invalid input
                break;

            case 4: // Numeric suffix state
                if (isalpha(c)) state = 3;  // Letter -> Return to state 3
                else if (isdigit(c)) state = 4;  // Digit -> Stay in state 4
                else return false;  // Invalid input
                break;

            case 5: // Rejecting state
                return false;  // Any input remains invalid
        }
    }

    // Accepting states: 2, 3, or 4
    return (state == 2 || state == 3 || state == 4);
}
