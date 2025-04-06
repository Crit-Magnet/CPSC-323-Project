#include <iostream>
#include <string>
#include <sstream>

#include "../Lexical Analyzer/lexer.h"
#include "syntax_rules.h"

// To get the source_code for lexer used in SA
std::string readFile()
{
    int argc = 3;
    std::string argv = "Lexical Analyzer/in1.txt";
     if (argc < 2) {
         std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
         return "";
     }

    // // Read file into a string
    std::fstream  file;
 	std::fstream* filePtr;
 	file.open(argv); // open input for parsing
 	filePtr = &file;

     if (!file) {
         std::cerr << "Error: Could not open file " << argv[1] << std::endl;
         return "";
     }

    std::stringstream buffer;
    buffer << filePtr->rdbuf();  // Read entire file into buffer
    std::string source_code = buffer.str();  // Convert to string

    // Open output file for writing
    std::ofstream output_file("Lexical Analyzer/output.txt");
    if (!output_file) {
        std::cerr << "Error: Could not open output.txt for writing." << std::endl;
        return "";
    }
    return source_code;
}

std::string file = readFile();

Token getNext()
{
	Token token = lexer(file)[0];
	return token;
}

Token token = getNext();
Token next  = getNext();


/*******************************************************************************
 * THESE RULES ARE ORDERED IN THE SAME ORDER AS DENOTED IN THE ASSIGNMENT
 ******************************************************************************/
// <Rat25S> ::= $$ <Opt Function Definitions> $$
//				<Opt Declaration List> $$ <Statement List> $$
void Rat25S()
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

// <Opt Function Definitions> ::= <Function Definitions> | <Empty>
void OptFunctionDefinitions()
{
	if(token.lexeme == "function")
	{
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

	Function();
	FunctionDefinitionsPrime();
	return;
}

//<Function Definitions>’ → <Function><Function Definitions>’ | ε
void FunctionDefinitionsPrime()
{
	if(token.type == "function")
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

// <Function> ::= function <Identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>
void Function()
{
	if(token.lexeme == "function")
	{
		token = getNext();

		if(token.type == "identifier")
		{
			token = getNext();

			if(token.lexeme == "(")
			{
				token = getNext();
				OptParameterList();
				if(token.lexeme != ")")
				{
					token = getNext();
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
		ParameterList();
	}
	else
	{
		Empty();
	}
	return;
}

// <Parameter List> → <Parameter> <Parameter List>’
void ParameterList()
{
	Parameter();
	ParameterListPrime();
	return;
}

//<Parameter List>’ → <Parameter> , <Parameter List>’ | ε
void ParameterListPrime()
{
	Parameter();
	if(token.lexeme == ",")
	{
		ParameterListPrime();
	}
	return;
}

// <Parameter> ::= <IDs > <Qualifier>
void Parameter()
{
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
		Statement();
	}
	else
	{
		Statement();
		StatementList();
	}
	return;
}

// <Declaration List> → <Declaration> ; <Declaration List>’
void DeclarationList()
{
	Declaration();
	if(token.lexeme == ";")
	{
		DeclarationListPrime();
	}
	return;
}

// <Declaration List>’ →  <Declaration> ; <Declaration List>’ | ε
void DeclarationListPrime()
{
	Declaration();
	if(token.lexeme == ";")
	{
		DeclarationListPrime();
	}
	else
	{
		Empty();
	}

	return;
}

//  <Declaration> ::= <Qualifier > <IDs>
void Declaration()
{
	//Qualifier();
	IDs();
	return;
}

// <IDs> → <Identifier> <IDs>’
void IDs()
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
		Statement();
	}
	else
	{
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

// <Compound> ::= { <Statement List> }
void Compound()
{
	if(token.lexeme == "{")
	{
		while(token.lexeme != "}")
		{
			StatementList();
		}
	}
	return;
}

// <Assign> ::= <Identifier> = <Expression> ;
void Assign()
{

	Expression();
	return;
}


// <If> ::= if ( <Condition> ) <Statement> <If'>
void If()
{
	return;
}

// <If'> ::= else if ( <Condition> ) <Statement> <If'>
// | else <Statement> endif
// | endif
void IfPrime()
{

	return ;
}



// <Return> ::= return ; | return <Expression> ;
void Return()
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
		Primary();
	}
	else
	{
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
		token = getNext();
		if(token.lexeme == "(")
		{
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
	return;
}






































