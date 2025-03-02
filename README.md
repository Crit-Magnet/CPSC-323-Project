# CPSC 323 Project
 Creating a compiler for the programming language Rat25s

# Project Structure

## **Source Files**
- `main.cpp` - Entry point of the lexer program.
- `lexer.cpp` - Implements the lexical analyzer.
- `lexer.h` - Header file for the lexer.
- `fsm_id.cpp` - Finite State Machine for identifier recognition.
- `fsm_id.h` - Header file for `fsm_id.cpp`.
- `fsm_number.cpp` - Finite State Machine for number recognition.
- `fsm_number.h` - Header file for `fsm_number.cpp`.

## **Header Files**
- `token.h` - Defines the `Token` structure.
- `keywords.h` - List of reserved keywords.
- `operators.h` - List of operators.
- `separators.h` - List of separators.

## **Test Files**
- `in1.txt` - Test case with **9** lines.
- `in2.txt` - Test case with **17** lines.
- `in3.txt` - Test case with **25** lines.
- `idtest.txt` - Identifier testing input.
- `numtest.txt` - Number testing input.

## **Expected Test Outputs**
- `in1output.txt` - Output for in1.txt.
- `in2output.txt` - Output for in2.txt.
- `in3output.txt` - Output for in3.txt.
- `idtestoutput.txt` - Output for idtest.txt.
- `numtestoutput.txt` - Output for numtest.txt.

## **Build and Configuration**
- `Makefile` - Compilation rules for building the project.

## **Documentation**
- `README.md` - Project overview and instructions.

---
### **Usage**
To compile the project using the Makefile:
```sh
make
