#include "../Lexical Analyzer/fsm_number.h"

#include <cctype>  // Needed for isalpha() and isalnum()

bool FSMnum(const std::string& lexeme) {
    int state = 1;

    for (char c : lexeme) {
        switch (state) {
            case 1:
                if (isdigit(c))
                    state = 2;
                else if (c == '.')
                    state = 5;  // Invalid: Number cannot start with '.'
                else
                    return false;
                break;

            case 2:
                if (isdigit(c))
                    state = 2;
                else if (c == '.')
                    state = 3;
                else
                    return false;
                break;

            case 3:
                if (isdigit(c))
                    state = 4;
                else
                    state = 5;  // Invalid: Decimal must be followed by a digit
                break;

            case 4:
                if (isdigit(c))
                    state = 4;
                else
                    state = 5;  // Invalid: No other characters allowed after digits
                break;

            case 5:
                return false;  // Already in error state
        }
    }

    // Accept only integers (state 2) and real numbers (state 4)
    return (state == 2 || state == 4);
}
