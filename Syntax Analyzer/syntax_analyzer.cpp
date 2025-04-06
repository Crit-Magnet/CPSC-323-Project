

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
	std::cout << token.lexeme << std::endl;
	if(token.lexeme == "$$")
	{
		std::cout << "<Opt Function Definitions>\n";
		token = getNext(source);
		std::cout << token.lexeme << std::endl;
		OptFunctionDefinitions();
	}
	if(token.lexeme == "$$")
	{
		std::cout << "<Opt Declaration List>\n";
		token = getNext(source);
		std::cout << token.lexeme << std::endl;
		OptDeclarationList();
	}
	if(token.lexeme == "$$")
	{
		std::cout << "<Statement List>\n";
		token = getNext(source);
		std::cout << token.lexeme << std::endl;
		StatementList();
	}
	std::cout <<"\nreturn from Rat25S\n";
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
		std::cout << "Function Def' empty\n";
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
		std::cout << token.lexeme << std::endl;
		if(token.type == "identifier")
		{
			token = getNext(source);
			std::cout << token.lexeme << std::endl;

			if(token.lexeme == "(")
			{
				std::cout << "function <Identifier> ( <Opt Parameter List>";
				token = getNext(source);
				std::cout << token.lexeme << std::endl;
				OptParameterList();
				std::cout << "RETURN FROM OPTPARAMLIST";
				if(token.lexeme == ")")
				{
					std::cout << "INSIDE OF )" << std::endl;
					std::cout << ") <Opt Declaration List> <Body>\n";
					token = getNext(source);
					std::cout << token.lexeme << std::endl;
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
		std::cout << "<Opt Parameter List> ::= <Parameter List> ->\n";
		ParameterList();
	}
	else if(token.type == "INVALID")
	{
		Empty();
	}
	return;
}

// <Parameter List> → <Parameter> <Parameter List>’
void ParameterList()
{
	std::cout << "<Parameter List> → <Parameter> <Parameter List>’ -> \n";
	Parameter();
	ParameterListPrime();
	return;
}

// <Parameter List>’ → <Parameter> , <Parameter List>’ | ε
void ParameterListPrime()
{
	std::cout << "<Parameter List>’ → <Parameter>\n";
	Parameter();
	if(token.lexeme == ",")
	{
		std::cout << ", <Parameter List>’\n";
		ParameterListPrime();
	}
	return;
}

// <Parameter> ::= <IDs > <Qualifier>
void Parameter()
{
	std::cout << "<Parameter> ::= <IDs> <Qualifier>\n";
	IDs();
	Qualifier();
	return;
}

// <Qualifier> ::= integer | boolean | real
void Qualifier()
{
	if(token.lexeme == "integer"
	    || token.lexeme == "boolean"
	    || token.lexeme == "real")
	{
		token = getNext(source);
		std::cout << token.lexeme << std::endl;
	}
	else
	{
		Empty();
	}
	return;
}

// <Body> ::= { < Statement List> }
void Body( )
{
	if(token.lexeme == "{")
	{
		std::cout << "<Body> ::= { < Statement List> }";
		std::cout <<"in Body\n";
		while(token.lexeme != "}")
		{
			StatementList();
		}
	}
	return;
}

// <Opt Declaration List> ::= <Declaration List> | <Empty>
void OptDeclarationList()
{
	if(token.type == "int" || token.type == "boolean" || token.type == "real")
	{
		std::cout << "<Opt Declaration List> ::= <Declaration List>\n";
		DeclarationList();
	}
	else if(token.type == "INVALID")
	{
		Empty();
	}
	return;
}

// <Declaration List> → <Declaration> ; <Declaration List>’
void DeclarationList()
{
	std::cout << "<Declaration List> → <Declaration>\n";
	Declaration();
	if(token.lexeme == ";")
	{
		std::cout << "; <Declaration List>’";
		token = getNext(source);
		std::cout << token.lexeme << std::endl;
		DeclarationListPrime();
	}
	return;
}

// <Declaration List>’ →  <Declaration> ; <Declaration List>’ | ε
void DeclarationListPrime()
{
	std::cout << "<Declaration List>’ →  <Declaration>\n";
	Declaration();
	if(token.lexeme == ";")
	{
		token = getNext(source);
		std::cout << token.lexeme << std::endl;
		std::cout << "; <Declaration List>’";
		DeclarationListPrime();
	}
	else if(token.type == "INVALID")
	{
		Empty();
	}

	return;
}

//  <Declaration> ::= <Qualifier > <IDs>
void Declaration()
{
	std::cout << "<Declaration> ::= <Qualifier> <IDs>\n";
	Qualifier();
	IDs();
	return;
}

// <IDs> → <Identifier> <IDs>’
void IDs()
{
//	std::cout <<"In ID" << token.type << std::endl;
	if(token.type == "identifier")
	{
		token = getNext(source);
		std::cout << token.lexeme << std::endl;

		// Check for a list of IDs separated by ','s
		while(true)
		{
			if(token.lexeme == ",")
			{
				token = getNext(source);
				std::cout << token.lexeme << std::endl;
				if(token.type == "identifier")
				{
					token = getNext(source);
					std::cout << token.lexeme << std::endl;
				}
			}
			else
			{
				break;
			}

		}
	}
	else
	{
		std::cout << "nothing id" << std::endl;
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
	std::cout << "<Statement List> -> <Statement> <Statement List>’\n";
	while(true)
	{
		Statement();
//		StatementListPrime();

		// Check to see if we have any statements
		// checks for the start of each statement
		if(token.lexeme  != "{" && token.type == "identifier"   &&
		    token.lexeme != "if" && token.lexeme != "print" 	&&
		    token.lexeme != "scan" &&token.lexeme != "return"   &&
		    token.lexeme != "while")
		{
			std::cout << "In statement List" << std::endl;
			break;
		}
	}
	return;
}

// <Statement List>’ →<Statement> <Statement List>’ | ε
//void StatementListPrime()
//{
//	// Check if Statement again
//	if(token.lexeme != "{" && token.type == "identifier"    &&
//			    token.lexeme != "if" && token.lexeme != "print" 	&&
//			    token.lexeme != "scan" &&token.lexeme != "return"   &&
//			    token.lexeme != "while")
//	{
//		Statement();
//		StatementListPrime();
//	}
//	else
//	{
//		Empty();
//	}
//	return;
//}

// <Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>
void Statement()
{
	if(token.lexeme == "{")
	{
		std::cout << "compound";
		Compound();
	}
	else if(token.type == "identifier")
	{
		std::cout << "assign";
		Assign();
	}
	else if(token.lexeme == "if")
	{
		std::cout << "if";
		If();
	}
	else if(token.lexeme == "return")
	{
		std::cout << "return";
		Return();
	}
	else if(token.lexeme == "print")
	{
		std::cout << "print";
		Print();
	}
	else if(token.lexeme == "scan")
	{
		std::cout << "scan";
		Scan();
	}
	else if(token.lexeme == "while")
	{
		std::cout << "while";
		While();
	}
	else
	{
		Empty();
	}

	return;
}

// <Compound> ::= { <Statement List> }
void Compound()
{
	if(token.lexeme == "{")
	{
		token = getNext(source);
		StatementList();
		token = getNext(source);
		if(token.lexeme != "}")
		{
			std::cout << "error\n";
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
	std::string temp2;
	Token temp = getNext(source);
	std::cout << temp.lexeme << std::endl;
	std::cin >>  temp2; // STOPS PROGRAM FOR DEBUG
	if(temp.lexeme == ";")
	{
		if(token.lexeme == "return")
		{
			token = temp;
			if(token.lexeme == ";")
			{
				token = getNext(source);
			}
			else
			{
				std::cout << "return error";
			}
		}
		else
		{
			if(token.lexeme == "return")
			{
				token = temp;
				Expression();
				if(token.lexeme == ";")
				{
					token = getNext(source);
				}
			}
		}
	}
	return;
}

// <Print> ::= print ( <Expression>);
void Print()
{
	if(token.lexeme == "print")
	{
		token = getNext(source);
		if(token.lexeme == "(")
		{
			Expression();
		}
	}
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
	Term();
	ExpressionPrime();
	return;
}

// <Expression>’ → +<Term><Expression>’ | - <Term><Expression>’ | ε
void ExpressionPrime()
{
	if(token.lexeme == "+")
	{
		token = getNext(source);
		Term();
		ExpressionPrime();
	}
	else if(token.lexeme == "-")
	{
		token = getNext(source);
		Term();
		ExpressionPrime();
	}
	else
	{
		Empty();
	}
	return;
}

// <Term> → <Factor><Term>’
void Term()
{
	Factor();
	TermPrime();
	return;
}

// <Term>’ → * <Factor><Term>’ | / <Factor><Term>’ | ε
void TermPrime()
{
	if(token.lexeme == "*" || token.lexeme == "/")
	{
		token = getNext(source);
		Factor();
		TermPrime();
	}
	else if(token.lexeme == "INVALID")
	{
		std::cout << "Error TermPrime";
	}
	else
	{
		Empty();
	}
	return;
}

// <Factor> ::= - <Primary> | <Primary>
void Factor()
{
	if(token.lexeme == "-")
	{
		std::cout << "<Factor> ::= - <Primary>";
		token = getNext(source);
		Primary();
	}
	else
	{
		std::cout << "<Factor> ::= <Primary>";
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
		std::cout << token.lexeme << std::endl;
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
	std::cout << "ε\n";
	return;
}






































