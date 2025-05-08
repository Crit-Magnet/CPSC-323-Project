# CPSC 323 Project
Creating a compiler for the programming language Rat25s

---

# Main Directory
- `LexicalAnalyzer` - Directory for the Lexical Analyzer
- `SyntaxAnalyzer` - Directory for the Syntax Analyzer
- `main.cpp` - Program entry point
- `Makefile` – Contains compilation rules using `g++`
- `README.md` – Project overview and instructions.

## LexicalAnalyzer
- `lexer.cpp` – Implements the lexical analyzer.
- `fsm_id.cpp` – Finite State Machine for identifier recognition.
- `fsm_number.cpp` – Finite State Machine for number recognition.

#### Header Files
- `lexer.h` – Header file for the lexer.
- `fsm_id.h` – Header file for `fsm_id.cpp`.
- `fsm_number.h` – Header file for `fsm_number.cpp`.
- `token.h` – Defines the `Token` structure.
- `keywords.h` – List of reserved keywords.
- `operators.h` – List of operators.
- `separators.h` – List of separators.

#### Test Files
- `in1.txt` – Test case with **<10** lines.
- `in2.txt` – Test case with **<21** lines.
- `in3.txt` – Test case with **>21** lines.
- `idtest.txt` – Identifier test case.
- `numtest.txt` – Number test case.
- `in1output.txt` – Output for `in1.txt`
- `in2output.txt` – Output for `in2.txt`
- `in3output.txt` – Output for `in3.txt`
- `idtestoutput.txt` – Output for `idtest.txt`
- `numtestoutput.txt` – Output for `numtest.txt`

## Syntax Analyzer
- `SyntaxAnalyzer.cpp` - Implements the syntax analyzer
- `SyntaxAnalyzer.h` - Header file for the syntax analyzer

#### Test Files
- `in1.txt` – Test case with **<10** lines.
- `in2.txt` – Test case with **<21** lines.
- `in3.txt` – Test case with **>21** lines.
- `in1output.txt` – Output for `in1.txt`
- `in2output.txt` – Output for `in2.txt`
- `in3output.txt` – Output for `in3.txt`


