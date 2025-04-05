#include "../Lexical Analyzer/lexer.h"
#include "syntax_analyzer.h"

/*******************************************************************************
 * THESE RULES ARE ORDERED IN THE SAME ORDER AS DENOTED IN THE ASSIGNMENT
 ******************************************************************************/
std::string file = readFile();

Token getNext()
{
	Token token = lexer(file)[0];
	return token;
}

void Empty(Token tem)
{
	return;
}

// LEFT RECUSTION
void Primary(Token tem)
{
	return;
}

void Factor(Token temp)
{
	if(true)
	{
		Primary();
	}
	else
	{
		Primary();
	}
	return;
}

// LEFT RECUSTION
void Term(Token tem)
{
	return;
}

// LEFT RECUSTION
void Expression(Token tem)
{
	return;
}

void Relop(Token temp)
{
	if(true)
	{
		temp = "==";
	}
	else if(true)
	{
		temp = "!=";
	}
	else if(true)
	{
		temp = ">";
	}
	else if(true)
	{
		temp = "<";
	}
	else if(true)
	{
		temp = ">=";
	}
	else
	{
		temp = "<=";
	}
	return;
}

void Condition(Token tem)
{
	Expression();
	Relop();
	Expression();
	return;
}

// LEFT RECUSTION
void While(Token tem)
{
	return;
}

// LEFT RECUSTION
void Scan(Token tem)
{
	return;
}

// LEFT RECUSTION
void Print(Token tem)
{
	return;
}

// LEFT RECUSTION
void Return(Token tem)
{
	if(true)
	{
		return;
	}
	else if(true)
	{
		return Expression();
	}
	return;
}

// BACKTRACKING & LEFT RECURSION
void If(Token tem)
{
	return;
}

// LEFT RECURSION
void Assign(Token tem)
{
	Token id;
	Token equal = "=";
	Expression();
	return;
}

void Compound(Token tem)
{
	//StatementList()
	return;
}

void Statement(Token tem)
{
	if(true)
	{
		Compound();
	}
	else if(true)
	{
		Assign();
	}
	else if(true)
	{
		If();
	}
	else if(true)
	{
		Return();
	}
	else if(true)
	{
		Print();
	}
	else if(true)
	{
		Scan();
	}
	else
	{
		While();
	}

	return;
}

void StatementList(Token tem)
{
	if(true)
	{
		Statement();
	}
	else
	{
		Statement();
		StatementList();
	}
	return;
}

void IDs(Token tem)
{
	if(true)
	{
		Token id;
	}
	else if(false)
	{
		Token id;
		IDs();
	}
	return;
}

//Move below Qualifier()
void Declaration(Token tem)
{
	//Qualifier();
	IDs();
	return;
}

// BACKTRACKING
void DeclarationList(Token tem)
{

	return;
}

void OptDeclarationList(Token tem)
{
	if(true)
	{
		Statement();
	}
	else
	{
		Statement();
		StatementList();
	}
	return;
}

void Body(Token tem)
{

	return;
}

void Qualifier(Token tem)
{
	if(true)
	{
		int temp;
	}
	else if(false)
	{
		bool b;
	}
	else
	{
		Token real;
	}
	return;
}

void Parameter(Token tem)
{
	IDs();
	Qualifier();
	return;
}

// BACKTRACKING
void ParameterList(Token tem)
{

	return;
}

void OptParameterList(Token tem)
{
	if(true)
	{
		ParameterList();
	}
	else
	{
		Empty();
	}
	return;
}

void Function(Token tem)
{

	return;
}

// BACKTRACKING
void FunctionDefinitionsPrime(Token tem)
{
	if(true)
	{
		Function();
		FunctionDefinitionsPrime();
	}
	else
	{
		Empty();
	}
	return;
}

void FunctionDefinitions(Token tem)
{
	Function();
	FunctionDefinitionsPrime();
	return;
}

void OptFunctionDefinitions()
{
	FunctionDefinitions();
	return;
}

void Rat25S(Token token)
{
	if(token.lexeme == "$$")
	{
		token = getNext();
		OptFunctionDefinitions();
	}
	if(token.lexeme == "$$")
	{
		token = getNext();
		OptDeclarationList();
	}
	if(token.lexeme == "$$")
	{
		token = getNext();
		StatementList();
	}
	return;
}



























