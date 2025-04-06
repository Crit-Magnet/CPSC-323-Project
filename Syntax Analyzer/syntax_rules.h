#ifndef SYNTAX_ANALYZER_SYNTAX_RULES_H_
#define SYNTAX_ANALYZER_SYNTAX_RULES_H_

std::string readFile();

void Rat25S();

void OptFunctionDefinitions();

void FunctionDefinitions( );

// BACKTRACKING
void FunctionDefinitionsPrime( );

void Function( );

void OptParameterList( );

// BACKTRACKING
void ParameterList( );

void ParameterListPrime();

void Parameter();

void Qualifier( );

void Body( );

void OptDeclarationList( );

// BACKTRACKING
void DeclarationList( );

void DeclarationListPrime();

void Declaration();

void IDs( );

void StatementList( );

void Statement( );

void Compound( );

// LEFT RECURSION
void Assign( );

// BACKTRACKING & LEFT RECURSION
void If( );

// LEFT RECUSTION
void Return( );


// LEFT RECUSTION
void Print( );

// LEFT RECUSTION
void Scan( );

// LEFT RECUSTION
void While( );

void Condition( );

void Relop();

// LEFT RECUSTION
void Expression( );

// LEFT RECUSTION
void Term( );

void Factor( );

// LEFT RECUSTION
void Primary( );

void Empty( );










































#endif /* SYNTAX_ANALYZER_SYNTAX_RULES_H_ */
