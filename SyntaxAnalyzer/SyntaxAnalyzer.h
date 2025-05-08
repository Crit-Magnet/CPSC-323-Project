#ifndef SYNTAX_ANALYZER_H
#define SYNTAX_ANALYZER_H

#include <ostream>
#include <string>

#include "token.h"

class SyntaxAnalyzer {
 public:
  void analyze(const std::string& source, std::ostream& output);
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

#endif  // SYNTAX_ANALYZER_H
