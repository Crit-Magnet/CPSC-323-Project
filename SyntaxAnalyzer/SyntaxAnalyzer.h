#ifndef SYNTAX_ANALYZER_H
#define SYNTAX_ANALYZER_H

#include <ostream>
#include <string>

#include "../LexicalAnalyzer/token.h"

class SyntaxAnalyzer {
 public:
  void analyze(const std::string& source, std::ostream& output);
};


// Item blueprint for symbol table
struct Symbol_Table_Item
{
	std::string id;
	int address;
	std::string type;
};

// Item blueprint for instruction table
struct Instr_Table_Item
{
	int address = 10000; // default address starting value in table
	std::string instr; // assembly instruction
	int operand; // varible address
};

// Utility functions
void printRule(const std::string& rule);
void match(const std::string& expected);
void syntaxError(const std::string& message);

// Grammar rule function declarations
void Rat25S();
void OptFunctionDefinitions();
void FunctionDefinitions();
void FunctionDefinitionsPrime();
void Function();
void OptParameterList();
void ParameterList();
void ParameterListPrime();
void Parameter();
void Qualifier();
void Body();
void OptDeclarationList();
void DeclarationList();
void DeclarationListPrime();
void Declaration();
void IDs();
void IDsPrime();
void StatementList();
void StatementListPrime();
void Statement();
void Compound();
void Assign();
void If();
void IfPrime();
void Return();
void Print();
void Scan();
void While();
void Condition();
void Relop();
void Expression();
void ExpressionPrime();
void Term();
void TermPrime();
void Factor();
void Primary();

// Object Code function declarations
int getAddress(std::string variable);
void generateInstruction(std::string instr, int address);
void backPatch(int instrAddress);
void storeAddress(std::string id, std::string address, std::string type);


#endif  // SYNTAX_ANALYZER_H
