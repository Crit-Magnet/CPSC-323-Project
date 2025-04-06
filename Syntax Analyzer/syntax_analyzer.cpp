

#include <iostream>
#include <string>
#include <sstream>

#include "../Lexical Analyzer/lexer.h"
#include "syntax_analyzer.h"

static std::string source = "";

Token getNext(std::string source_code)
{
	Token token = lexer(source_code)[0];
	return token;
}

Token token;
Token nextToken;
/*******************************************************************************
 * THESE RULES ARE ORDERED IN THE SAME ORDER AS DENOTED IN THE ASSIGNMENT
 ******************************************************************************/
// <Rat25S> ::= $$ <Opt Function Definitions> $$
//				<Opt Declaration List> $$ <Statement List> $$
void Rat25S(std::string source_code)
{
	source = source_code;
	token = getNext(source);
	if(token.lexeme == "$$")
	{
		std::cout << "<Opt Function Definitions>\n";
		token = getNext(source);
		OptFunctionDefinitions();
	}
	if(token.lexeme == "$$")
	{
		std::cout << "<Opt Declaration List>\n";
		token = getNext(source);
		OptDeclarationList();
	}
	if(token.lexeme == "$$")
	{
		std::cout << "<Statement List>\n";
		token = getNext(source);
		StatementList();
	}
	return;
}

// <Opt Function Definitions> ::= <Function Definitions> | <Empty>
void OptFunctionDefinitions()
{
	if(token.lexeme == "function")
	{
		std::cout << "<Opt Function Definitions> ::= <Function Definitions>\n";
		FunctionDefinitions();
	}
	else
	{
		Empty();
	}
	return;
}

// <Function Definitions> → <Function><Function Definitions>’
void FunctionDefinitions()
{
	if(token.lexeme != "function")
	{
		return;
	}

	std::cout << "<Function Definitions> → <Function><Function Definitions>’\n";
	Function();
	FunctionDefinitionsPrime();
	return;
}

// <Function Definitions>’ → <Function><Function Definitions>’ | ε
void FunctionDefinitionsPrime()
{
	if(token.type == "function")
	{
		std::cout << "<Function Definitions>’ → <Function><Function Definitions>’\n";
		Function();
		FunctionDefinitionsPrime();
	}
	else
	{
		std::cout << "";
		Empty();
	}
	return;
}

// <Function> ::= function <Identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>
void Function()
{
	if(token.lexeme == "function")
	{
		token = getNext(source);

		if(token.type == "identifier")
		{
			token = getNext(source);

			if(token.lexeme == "(")
			{
				std::cout << "";
				token = getNext(source);
				OptParameterList();
				if(token.lexeme != ")")
				{
					std::cout << "";
					token = getNext(source);
					OptDeclarationList();
					Body();
				}

			}
		}

	}
	return;
}

// <Opt Parameter List> ::= <Parameter List> | <Empty>
void OptParameterList()
{
	if(token.type == "identifier")
	{
		std::cout << "";
		ParameterList();
	}
	else
	{
		std::cout << "";
		Empty();
	}
	return;
}

// <Parameter List> → <Parameter> <Parameter List>’
void ParameterList()
{
	std::cout << "";
	Parameter();
	ParameterListPrime();
	return;
}

//<Parameter List>’ → <Parameter> , <Parameter List>’ | ε
void ParameterListPrime()
{
	std::cout << "";
	Parameter();
	if(token.lexeme == ",")
	{
		std::cout << "";
		ParameterListPrime();
	}
	return;
}

// <Parameter> ::= <IDs > <Qualifier>
void Parameter()
{
	std::cout << "";
	IDs();
	Qualifier();
	return;
}

// <Qualifier> ::= integer | boolean | real
void Qualifier()
{
	if(token.type == "integer")
	{

	}
	else if(token.type == "boolean")
	{
	}
	else
	{

	}
	return;
}

// <Body> ::= { < Statement List> }
void Body( )
{
	if(token.lexeme == "{")
	{
		while(token.lexeme != "}")
		{
			std::cout << "";
			StatementList();
		}
	}
	return;
}

// <Opt Declaration List> ::= <Declaration List> | <Empty>
void OptDeclarationList()
{
	if(true)
	{
		std::cout << "";
		Statement();
	}
	else
	{
		std::cout << "";
		Statement();
		StatementList();
	}
	return;
}

// <Declaration List> → <Declaration> ; <Declaration List>’
void DeclarationList()
{
	std::cout << "";
	Declaration();
	if(token.lexeme == ";")
	{
		std::cout << "";
		DeclarationListPrime();
	}
	return;
}

// <Declaration List>’ →  <Declaration> ; <Declaration List>’ | ε
void DeclarationListPrime()
{
	std::cout << "";
	Declaration();
	if(token.lexeme == ";")
	{
		std::cout << "";
		DeclarationListPrime();
	}
	else
	{
		std::cout << "";
		Empty();
	}

	return;
}

//  <Declaration> ::= <Qualifier > <IDs>
void Declaration()
{
	std::cout << "";
	Qualifier();
	if(token.lexeme == ">")
	{
		std::cout << "";
		IDs();
	}
	return;
}

// <IDs> → <Identifier> <IDs>’
void IDs()
{
	if(token.type == "identfier")
	{
		token = getNext(source);
	}

	if(token.lexeme == ",")
	{
		token = getNext(source);
		if(token.type == "identifier")
		{
			token = getNext(source);
		}
	}
	else
	{
		return;
	}
	return;
}

// <IDs>’ → <Identifier>, <IDs>’ | ε
void IDsPrime()
{

	return;
}

// <Statement List> -> <Statement> <Statement List>’
void StatementList()
{
	if(true)
	{
		std::cout << "";
		Statement();
	}
	else
	{
		std::cout << "";
		Statement();
		StatementList();
	}
	return;
}

// <Statement List>’ →<Statement> <Statement List>’ | ε
void StatementListPrime()
{

	return;
}

// <Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>
void Statement()
{
	if(token.lexeme == "{")
	{
		std::cout << "";
		Compound();
	}
	else if(true)
	{
		std::cout << "";
		Assign();
	}
	else if(true)
	{
		std::cout << "";
		If();
	}
	else if(true)
	{
		std::cout << "";
		Return();
	}
	else if(true)
	{
		std::cout << "";
		Print();
	}
	else if(true)
	{
		std::cout << "";
		Scan();
	}
	else
	{
		std::cout << "";
		While();
	}

	return;
}

// <Compound> ::= { <Statement List> }
void Compound()
{
	if(token.lexeme == "{")
	{
		while(token.lexeme != "}")
		{
			std::cout << "";
			StatementList();
		}
	}
	return;
}

// <Assign> ::= <Identifier> = <Expression> ;
void Assign()
{
	std::cout << "";
	Expression();
	return;
}


// <If> ::= if ( <Condition> ) <Statement> <If'>
void If()
{
	std::cout << "";
	return;
}

// <If'> ::= else if ( <Condition> ) <Statement> <If'>
// | else <Statement> endif
// | endif
void IfPrime()
{
	std::cout << "";
	return ;
}



// <Return> ::= return ; | return <Expression> ;
void Return()
{
	if(true)
	{
		std::cout << "";
		return;
	}
	else if(true)
	{
		std::cout << "";
		return Expression();
	}
	return;
}

// <Print> ::= print ( <Expression>);
void Print()
{
	return;
}

// <Scan> ::= scan ( <IDs> );
void Scan()
{
	return;
}

// <While> ::= while ( <Condition> ) <Statement> endwhile
void While()
{
	return;
}

// <Condition> ::= <Expression> <Relop> <Expression>
void Condition()
{
	std::cout << "";
	Expression();
	Relop();
	Expression();
	return;
}

// <Relop> ::= == | != | > | < | <= | =>
void Relop()
{
	if(token.lexeme == "==")
	{

	}
	else if(token.lexeme == "!=")
	{

	}
	else if(token.lexeme == ">")
	{

	}
	else if(token.lexeme == "<")
	{

	}
	else if(token.lexeme == ">=")
	{

	}
	else
	{

	}
	return;
}

// <Expression> →  <Term><Expression>’
void Expression()
{
	return;
}

// <Expression>’ → +<Term><Expression>’ | - <Term><Expression>’ | ε
void ExpressionPrime()
{
	return;
}

// <Term> → <Factor><Term>’
void Term()
{
	return;
}

// <Term>’ → * <Factor><Term>’ | / <Factor><Term>’ | ε
void TermPrime()
{
	return;
}

// <Factor> ::= - <Primary> | <Primary>
void Factor()
{
	if(token.lexeme == "-")
	{
		std::cout << "";
		Primary();
	}
	else
	{
		std::cout << "";
		Primary();
	}
	return;
}

// <Primary> ::= <Identifier> | <Integer> | <Identifier> ( <IDs> )
// 				| ( <Expression> ) |<Real> | true | false
void Primary()
{
	if(token.type == "identifier")
	{
		token = getNext(source);
		if(token.lexeme == "(")
		{
			std::cout << "";
			IDs();
		}
	}
	else if(token.type == "integer")
	{

	}
	else if(token.type == "")
	return;
}

// <Empty> ::= ε
void Empty()
{
	std::cout << "";
	return;
}






































