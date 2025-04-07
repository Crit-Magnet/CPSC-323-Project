

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
std::string stopper;
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
		std::cin >> stopper;
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
	std::cout << "<Function Definitions>’ ::=";
	if(token.type == "function")
	{
		std::cout << "<Function><Function Definitions>’\n";
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
		token = getNext(source);
		StatementList();
		if(token.lexeme == "}")
		{
			token = getNext(source);
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
	if(token.lexeme == ",")
	{
		token = getNext(source);
		IDs();
		IDsPrime();
	}
	return;
}

// <Statement List> -> <Statement> <Statement List>’
void StatementList()
{
	std::cout << "<Statement List> -> <Statement> <Statement List>’\n";
	bool statement = true;
	while(statement)
	{
		Statement();
//		StatementListPrime();

		// Check to see if we have any statements
		// checks for the start of each statement
		if(token.lexeme  != "{" && token.type != "identifier"   &&
		    token.lexeme != "if" && token.lexeme != "print" 	&&
		    token.lexeme != "scan" &&token.lexeme != "return"   &&
		    token.lexeme != "while")
		{
			std::cout << "Not statement" << std::endl;
			statement = false;
		}

		std::cout << token.lexeme;
		std::cout << "StatementList stopper";
		std::cin >> stopper;
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
	std::cout << "<Statement> ::= ";
	if(token.lexeme == "{")
	{
		std::cout << "<Compound>";
		Compound();
	}
	else if(token.type == "identifier")
	{
		std::cout << "<Assign>";
		Assign();
	}
	else if(token.lexeme == "if")
	{
		std::cout << "If";
		If();
	}
	else if(token.lexeme == "return")
	{
		std::cout << "<Return>";
		Return();
	}
	else if(token.lexeme == "print")
	{
		std::cout << "<Print>";
		Print();
	}
	else if(token.lexeme == "scan")
	{
		std::cout << "<Scan>";
		Scan();
	}
	else if(token.lexeme == "while")
	{
		std::cout << "<While>";
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
			std::cout << "Error, missing '}' for compound.\n";
		}
	}
	else
	{
		std::cout << "Error, missing '{' for compound.\n";
	}
	return;
}

// <Assign> ::= <Identifier> = <Expression> ;
void Assign()
{
	std::cout << "<Identifier> = <Expression> ;";
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
	return;
}



// <Return> ::= return ; | return <Expression> ;
void Return()
{
	Token temp;
	std::cout << "temp" << temp.lexeme << std::endl;


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
	}
	else
	{
		if(token.lexeme == "return")
		{
//			token = temp;
			token = getNext(source);
			std::cout << "in return" <<token.lexeme;
			Expression();
			if(token.lexeme == ";")
			{
				token = getNext(source);
				std::cout << "Token after expressions" << token.lexeme;
			}
			else
			{
				std::cout << "Error, missing ';' after return\n";
			}
		}
		else
		{
			std::cout << "Error, missing return value.\n";
		}
	}
//	token = temp;
	std::cout << "Return stopper";
	std::cin >>  stopper; // STOPS PROGRAM FOR DEBUG
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
	if(token.lexeme == "scan")
	{
		token = getNext(source);
		if(token.lexeme == "(")
		{
			IDs();
		}
	}
	return;
}

// <While> ::= while ( <Condition> ) <Statement> endwhile
void While()
{
	if(token.lexeme == "while")
	{
		token = getNext(source);
		if(token.lexeme == "(")
		{
			token = getNext(source);
			Condition();
			if(token.lexeme == ")")
			{
				token = getNext(source);
				Statement();
			}
			else
			{
				std::cout << "Error, missing ')' in while\n";
			}
		}
		else
		{
			std:: cout << "Error, missing '(' in while.\n";
		}
	}
	else
	{
		std::cout << "Error, missing 'while' keyword.\n";
	}
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
	std::cout << "<Expression> →  <Term><Expression>’\n";
	Term();
	ExpressionPrime();
	return;
}

// <Expression>’ → +<Term><Expression>’ | - <Term><Expression>’ | ε
void ExpressionPrime()
{
	std::cout << " <Expression>’ ::= ";
	if(token.lexeme == "+")
	{
		std::cout << "+ <Term><Expression>’\n";
		token = getNext(source);
		Term();
		ExpressionPrime();
	}
	else if(token.lexeme == "-")
	{
		std::cout << "- <Term><Expression>’ \n";
		token = getNext(source);
		Term();
		ExpressionPrime();
	}
	else if(token.lexeme == "INVALID")
	{
		std::cout << "Error, Expression";
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
	std::cout << "<Term> → <Factor><Term>’\n";
	Factor();
	TermPrime();
	return;
}

// <Term>’ → * <Factor><Term>’ | / <Factor><Term>’ | ε
void TermPrime()
{
	std::cout << "<Term>’ ::= ";
	if(token.lexeme == "*")
	{
		std::cout << "* <Factor><Term>’\n";
		token = getNext(source);
		Factor();
		TermPrime();
	}
	else if(token.lexeme == "/")
	{
		std::cout << "/ <Factor><Term>’\n";
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
	std::cout << "<Factor> ::= ";
	if(token.lexeme == "-")
	{
		std::cout << "- <Primary>\n";
		token = getNext(source);
		Primary();
	}
	else
	{
		std::cout << "<Primary>\n";
		Primary();
	}
	return;
}

// <Primary> ::= <Identifier> | <Integer> | <Identifier> ( <IDs> )
// 				| ( <Expression> ) |<Real> | true | false
void Primary()
{
	std::cout << "<Primary> ::= ";
	if(token.type == "identifier")
	{
		token = getNext(source);
//		std::cout << token.lexeme << std::endl;
		if(token.lexeme == "(")
		{
			std::cout << "<Identifier> ( <IDs> )\n";
			token = getNext(source);
			IDs();
			if(token.lexeme == ")")
			{
				token = getNext(source);
			}
			else
			{
				std::cout << "Error, missing ')' for (IDs) Primary.\n";
			}
		}
		else
		{
			std::cout << "<Identifier>\n";
		}

	}
	else if(token.type == "integer")
	{
		std::cout << "<Integer>\n";
		token = getNext(source);
	}
	else if(token.lexeme == "(")
	{
		std::cout << "( <Expression> )\n";
		token = getNext(source);
		Expression();
		if(token.lexeme == ")")
		{
			token = getNext(source);
		}
		else
		{
			std::cout << "Error, missing ')' for Expression in Primary.\n";
		}
	}
	else if(token.type == "real")
	{
		std::cout << "<Real>\n";
		token = getNext(source);
	}
	else if(token.lexeme == "true")
	{
		std::cout << "true\n";
		token = getNext(source);
	}
	else if(token.lexeme == "false")
	{
		std::cout << "false\n";
		token = getNext(source);
	}
	else
	{
		std::cout << "An unknown error has occured inside of Primary.";
	}
	return;
}

// <Empty> ::= ε
void Empty()
{
	std::cout << "ε\n";
	return;
}






































