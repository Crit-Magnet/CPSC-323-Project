#include "SyntaxAnalyzer.h"

#include <cstdlib>
#include <iostream>
#include <vector>

#include "lexer.h"

// Global parsing state
std::vector<Token> tokens;
unsigned int index = 0;
Token token;
std::ostream* out = nullptr;

// Print a grammar rule being applied
void printRule(const std::string& rule) { *out << rule << std::endl; }

// Advance to the next token
void advance() {
  if (++index >= tokens.size()) {
    syntaxError("Unexpected end of input");
  }
  token = tokens[index];
}

// Match a token by expected type or lexeme
void match(const std::string& expected) {
  if (token.lexeme == expected || token.type == expected) {
    *out << "Token: " << token.type << "   Lexeme: " << token.lexeme << "\n";
    advance();
  } else {
    syntaxError("expected '" + expected + "', but got '" + token.lexeme + "'");
  }
}

// Handle syntax errors with detailed messaging
void syntaxError(const std::string& message) {
  if (out) {
    *out << "Syntax Error: " << message << " (token: '" << token.lexeme
         << "', type: " << token.type << ")\n";
  } else {
    std::cerr << "Syntax Error: " << message << " (token: '" << token.lexeme
              << "', type: " << token.type << ")\n";
  }
}

// Entry point for parsing the input source code
void SyntaxAnalyzer::analyze(const std::string& source, std::ostream& output) {
  tokens = lexer(source);
  index = 0;
  out = &output;

  if (tokens.empty()) {
    syntaxError("Empty input");
  }

  token = tokens[index];

  Rat25S();
}

// === Grammar Rule Implementations ===

// R1: <Rat25S> ::= $$ <Opt Function Definitions> $$ <Opt Declaration List> $$
// <Statement List> $$
void Rat25S() {
  printRule(
      "   <Rat25S> ::= $$ <Opt Function Definitions> $$ <Opt Declaration List> "
      "$$ <Statement List> $$");

  match("$$");
  OptFunctionDefinitions();
  match("$$");
  OptDeclarationList();
  match("$$");
  StatementList();
  match("$$");
}

// R2: <Opt Function Definitions> ::= <Function Definitions> | ε
void OptFunctionDefinitions() {
  if (token.lexeme == "function") {
    printRule("   <Opt Function Definitions> ::= <Function Definitions>");
    FunctionDefinitions();
  } else {
    printRule("   <Opt Function Definitions> ::= ε");
  }
}

// R3: <Function Definitions> ::= <Function> <Function Definitions>'
void FunctionDefinitions() {
  printRule("   <Function Definitions> ::= <Function> <Function Definitions>'");
  Function();
  FunctionDefinitionsPrime();
}

// R4: <Function Definitions>' ::= <Function> <Function Definitions>' | ε
void FunctionDefinitionsPrime() {
  if (token.lexeme == "function") {
    printRule(
        "   <Function Definitions>' ::= <Function> <Function Definitions>'");
    Function();
    FunctionDefinitionsPrime();
  } else {
    printRule("   <Function Definitions>' ::= ε");
  }
}

// R5: <Function> ::= function <Identifier> ( <Opt Parameter List> ) <Opt
// Declaration List> <Body>
void Function() {
  printRule(
      "   <Function> ::= function <Identifier> ( <Opt Parameter List> ) <Opt "
      "Declaration List> <Body>");
  match("function");
  match("identifier");
  match("(");
  OptParameterList();
  match(")");
  OptDeclarationList();
  Compound();
}

// R6: <Opt Parameter List> ::= <Parameter List> | ε
void OptParameterList() {
  if (token.type == "identifier") {
    printRule("   <Opt Parameter List> ::= <Parameter List>");
    ParameterList();
  } else {
    printRule("   <Opt Parameter List> ::= ε");
  }
}

// R7: <Parameter List> ::= <Parameter> <Parameter List>'
void ParameterList() {
  printRule("   <Parameter List> ::= <Parameter> <Parameter List>'");
  Parameter();
  ParameterListPrime();
}

// R8: <Parameter List>' ::= , <Parameter> <Parameter List>' | ε
void ParameterListPrime() {
  if (token.lexeme == ",") {
    printRule("   <Parameter List>' ::= , <Parameter> <Parameter List>'");
    match(",");
    Parameter();
    ParameterListPrime();
  } else {
    printRule("   <Parameter List>' ::= ε");
  }
}

// R9: <Parameter> ::= <IDs> <Qualifier>
void Parameter() {
  printRule("   <Parameter> ::= <IDs> <Qualifier>");
  IDs();
  Qualifier();
}

// R10: <Qualifier> ::= integer | boolean | real
void Qualifier() {
  if (token.lexeme == "integer" || token.lexeme == "boolean" ||
      token.lexeme == "real") {
    printRule("   <Qualifier> ::= " + token.lexeme);
    match(token.lexeme);
  } else {
    syntaxError("Qualifier");
  }
}

// R11: <Body> ::= { <Statement List> }
void Compound() {
  printRule("   <Body> ::= { <Statement List> }");
  match("{");
  StatementList();
  match("}");
}

// R12: <Opt Declaration List> ::= <Declaration List> | ε
void OptDeclarationList() {
  if (token.lexeme == "integer" || token.lexeme == "boolean" ||
      token.lexeme == "real") {
    printRule("   <Opt Declaration List> ::= <Declaration List>");
    DeclarationList();
  } else {
    printRule("   <Opt Declaration List> ::= ε");
  }
}

// R13: <Declaration List> ::= <Declaration> ; <Declaration List>'
void DeclarationList() {
  printRule("   <Declaration List> ::= <Declaration> ; <Declaration List>'");
  Declaration();
  match(";");
  DeclarationListPrime();
}

// R14: <Declaration List>' ::= <Declaration> ; <Declaration List>' | ε
void DeclarationListPrime() {
  if (token.lexeme == "integer" || token.lexeme == "boolean" ||
      token.lexeme == "real") {
    printRule("   <Declaration List>' ::= <Declaration> ; <Declaration List>'");
    Declaration();
    match(";");
    DeclarationListPrime();
  } else {
    printRule("   <Declaration List>' ::= ε");
  }
}

// R15: <Declaration> ::= <Qualifier> <IDs>
void Declaration() {
  printRule("   <Declaration> ::= <Qualifier> <IDs>");
  Qualifier();
  IDs();
}

// R16: <IDs> ::= identifier <IDs>'
void IDs() {
  printRule("   <IDs> ::= identifier <IDs>'");
  match("identifier");
  IDsPrime();
}

// R17: <IDs>' ::= , identifier <IDs>' | ε
void IDsPrime() {
  if (token.lexeme == ",") {
    printRule("   <IDs>' ::= , identifier <IDs>'");
    match(",");
    match("identifier");
    IDsPrime();
  } else {
    printRule("   <IDs>' ::= ε");
  }
}

// R18: <Statement List> ::= <Statement> <Statement List>'
void StatementList() {
  printRule("   <Statement List> ::= <Statement> <Statement List>'");
  Statement();
  StatementListPrime();
}

// R19: <Statement List>' ::= <Statement> <Statement List>' | ε
void StatementListPrime() {
  if (token.lexeme == "{" || token.type == "identifier" ||
      token.lexeme == "if" || token.lexeme == "return" ||
      token.lexeme == "print" || token.lexeme == "scan" ||
      token.lexeme == "while") {
    printRule("   <Statement List>' ::= <Statement> <Statement List>'");
    Statement();
    StatementListPrime();
  } else {
    printRule("   <Statement List>' ::= ε");
  }
}

// R20: <Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> |
// <Scan> | <While>
void Statement() {
  if (token.lexeme == "{") {
    printRule("   <Statement> ::= <Compound>");
    Compound();
  } else if (token.type == "identifier") {
    printRule("   <Statement> ::= <Assign>");
    Assign();
  } else if (token.lexeme == "if") {
    printRule("   <Statement> ::= <If>");
    If();
  } else if (token.lexeme == "return") {
    printRule("   <Statement> ::= <Return>");
    Return();
  } else if (token.lexeme == "print") {
    printRule("   <Statement> ::= <Print>");
    Print();
  } else if (token.lexeme == "scan") {
    printRule("   <Statement> ::= <Scan>");
    Scan();
  } else if (token.lexeme == "while") {
    printRule("   <Statement> ::= <While>");
    While();
  } else {
    syntaxError("Statement");
  }
}

// R21: <Assign> ::= <Identifier> = <Expression> ;
void Assign() {
  printRule("   <Assign> ::= <Identifier> = <Expression> ;");
  match("identifier");
  match("=");
  Expression();
  match(";");
}

// R22: <If> ::= if ( <Condition> ) <Statement> <If'>
void If() {
  printRule("   <If> ::= if ( <Condition> ) <Statement> <If'>");
  match("if");
  match("(");
  Condition();
  match(")");
  Statement();
  IfPrime();
}

// R23: <If'> ::= endif | else <Statement> endif
void IfPrime() {
  if (token.lexeme == "else") {
    printRule("   <If'> ::= else <Statement> endif");
    match("else");
    Statement();
    match("endif");
  } else if (token.lexeme == "endif") {
    printRule("   <If'> ::= endif");
    match("endif");
  } else {
    syntaxError("endif or else");
  }
}

// R24: <Return> ::= return ; | return <Expression> ;
void Return() {
  printRule("   <Return> ::= return ; | return <Expression> ;");
  match("return");
  if (token.lexeme == ";") {
    match(";");
  } else {
    Expression();
    match(";");
  }
}

// R25: <Print> ::= print ( <Expression> );
void Print() {
  printRule("   <Print> ::= print ( <Expression> );");
  match("print");
  match("(");
  Expression();
  match(")");
  match(";");
}

// R26: <Scan> ::= scan ( <IDs> );
void Scan() {
  printRule("   <Scan> ::= scan ( <IDs> );");
  match("scan");
  match("(");
  IDs();
  match(")");
  match(";");
}

// R27: <While> ::= while ( <Condition> ) <Statement> endwhile
void While() {
  printRule("   <While> ::= while ( <Condition> ) <Statement> endwhile");
  match("while");
  match("(");
  Condition();
  match(")");
  Statement();
  match("endwhile");
}

// R28: <Condition> ::= <Expression> <Relop> <Expression>
void Condition() {
  printRule("   <Condition> ::= <Expression> <Relop> <Expression>");
  Expression();
  Relop();
  Expression();
}

// R29: <Relop> ::= == | != | > | < | <= | >=
void Relop() {
  if (token.lexeme == "==" || token.lexeme == "!=" || token.lexeme == "<" ||
      token.lexeme == ">" || token.lexeme == "<=" || token.lexeme == ">=") {
    printRule("   <Relop> ::= " + token.lexeme);
    match(token.lexeme);
  } else {
    syntaxError("Relop");
  }
}

// R30: <Expression> ::= <Term> <Expression'>
void Expression() {
  printRule("   <Expression> ::= <Term> <Expression'>");
  Term();
  ExpressionPrime();
}

// R31: <Expression'> ::= +|− <Term> <Expression'> | ε
void ExpressionPrime() {
  if (token.lexeme == "+" || token.lexeme == "-") {
    printRule("   <Expression'> ::= +|− <Term> <Expression'>");
    match(token.lexeme);
    Term();
    ExpressionPrime();
  } else {
    printRule("   <Expression'> ::= ε");
  }
}

// R32: <Term> ::= <Factor> <Term'>
void Term() {
  printRule("   <Term> ::= <Factor> <Term'>");
  Factor();
  TermPrime();
}

// R33: <Term'> ::= *|/ <Factor> <Term'> | ε
void TermPrime() {
  if (token.lexeme == "*" || token.lexeme == "/") {
    printRule("   <Term'> ::= *|/ <Factor> <Term'>");
    match(token.lexeme);
    Factor();
    TermPrime();
  } else {
    printRule("   <Term'> ::= ε");
  }
}

// R34: <Factor> ::= - <Primary> | <Primary>
void Factor() {
  if (token.lexeme == "-") {
    printRule("   <Factor> ::= - <Primary>");
    match("-");
    Primary();
  } else {
    printRule("   <Factor> ::= <Primary>");
    Primary();
  }
}

// R35: <Primary> ::= identifier [ ( <IDs> ) ] | integer | real | ( <Expression>
// ) | true | false
void Primary() {
  if (token.type == "identifier") {
    match("identifier");
    if (token.lexeme == "(") {
      match("(");
      IDs();
      match(")");
    }
  } else if (token.type == "integer") {
    match("integer");
  } else if (token.type == "real") {
    match("real");
  } else if (token.lexeme == "(") {
    match("(");
    Expression();
    match(")");
  } else if (token.lexeme == "true" || token.lexeme == "false") {
    match(token.lexeme);
  } else {
    syntaxError("Primary");
  }
}
