#include "../SyntaxAnalyzer/SyntaxAnalyzer.h"

#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>

#include "../LexicalAnalyzer/lexer.h"


// Global parsing state
std::vector<Token> tokens;

// Symbol Table for Object Code
std::vector<Symbol_Table_Item> symbolTable;
std::string datatype = "";

// Instruction Table for Object Code
std::vector<Instr_Table_Item> instrTable;

unsigned int index = 0;
Token token;

std::string save = "";     // for passing variable to getAddress()
int instrAdd = 0; 	       // for passing instruction addresses
std::stack<int> JUMPStack; // used for backpatching
bool relational = 0;       // check for relational for second param

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


/*******************************************************************************
 ====================== Grammar Rule Implementations ==========================
*******************************************************************************/

// R1: <Rat25S> ::= $$ <Opt Function Definitions> $$ <Opt Declaration List> $$
// <Statement List> $$
void Rat25S() {
  printRule(
      "   <Rat25S> ::= $$ <Opt Declaration List> "
      "$$ <Statement List> $$");

  match("$$");
  OptDeclarationList();
  match("$$");
  StatementList();
  match("$$");
  std::cout << "outputting symboltable\n";

  for(int i = 0; i < symbolTable.size(); i++)
  {
	  std::cout << symbolTable[i].id;
	  std::cout << '\t' << symbolTable[i].address;
	  std::cout << '\t' << symbolTable[i].type << std::endl;
  }

  std::cout << "\n\noutputting Instruction Table\n";
  for(int i = 0; i < instrTable.size(); i++)
  {
	  std::cout << instrTable[i].address + 1;
	  std::cout << '\t' << instrTable[i].instr;
	  std::cout << '\t' << instrTable[i].operand << std::endl;
  }
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

// R10: <Qualifier> ::= integer | boolean
void Qualifier() {
  if (token.lexeme == "integer" || token.lexeme == "boolean")
  {
    printRule("   <Qualifier> ::= " + token.lexeme);
    datatype = token.lexeme; // Check for variable type for symbol table
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
  if (token.lexeme == "integer" || token.lexeme == "boolean"){
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
  if (token.lexeme == "integer" || token.lexeme == "boolean") {
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

  // check if variable is already in symbol table
  // Have to check all instances here as well in case
  //  we have integers and booleans declared in a file since
  //  we create variables of a type until ';'
  bool temp = 0;
  for(int i = 0; i < symbolTable.size(); i++)
  {
	  if(symbolTable[i].id == token.lexeme)
	  {
		  std::cout << "in symbol table\n";
		  temp = 1;
		  break;
	  }
  }
  if(!temp)
  {
		Symbol_Table_Item temp;
		temp.id 	   = token.lexeme;
		temp.address = 10000+symbolTable.size(); // Start at address 10000
		temp.type    = datatype;
		symbolTable.push_back(temp);
  }
  match("identifier");

  IDsPrime();
}

// R17: <IDs>' ::= , identifier <IDs>' | ε
void IDsPrime() {
  if (token.lexeme == ",") {
    printRule("   <IDs>' ::= , identifier <IDs>'");

    match(",");

    // check if variable is already in symbol table
	bool temp = 0;
	for(int i = 0; i < symbolTable.size(); i++)
	{
		if(symbolTable[i].id == token.lexeme)
		{
			std::cout << token.lexeme << " in symbol table\n";
			temp = 1;
			break;
		}
	}
	if(!temp)
	{
		Symbol_Table_Item temp;
		temp.id 	   = token.lexeme;
		temp.address = 10000 + symbolTable.size(); // Start at address 10000
		temp.type    = datatype;
		symbolTable.push_back(temp);
	}
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
  save = token.lexeme;
  match("identifier");
  match("=");
  Expression();
  generateInstruction("POPM", getAddress(save));
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
  backPatch(instrAdd);
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
  instrAdd = instrTable.size();
  generateInstruction("LABEL", -1);
  match("while");
  match("(");
  Condition();
  match(")");
  Statement();
  generateInstruction("JUMP", instrAdd+1);
  backPatch(instrTable.size());
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

    if(token.lexeme == "==")
    {
    	generateInstruction("EQU",-1);
    	JUMPStack.push(instrTable.size());
    	generateInstruction("JMP0", -1);
    }
    else if(token.lexeme == "!=")
    {
    	generateInstruction("NEQ",-1);
    	JUMPStack.push(instrTable.size());
    	generateInstruction("JMP0", -1);
    }
    else if(token.lexeme == "<")
    {
    	generateInstruction("LES",-1);
    	std::cout << "RELATIONAL INSTRADD" << instrTable.size();
    	JUMPStack.push(instrTable.size());
    	generateInstruction("JMP0", -1);
    }
    else if(token.lexeme == ">")
    {
    	generateInstruction("GRT",-1);
    	JUMPStack.push(instrTable.size());
    	generateInstruction("JMP0", -1);
    }
    else if(token.lexeme == "<=")
    {
    	generateInstruction("LEQ",-1);
    	JUMPStack.push(instrTable.size());
    	generateInstruction("JUMP0", -1);
    }
    else if(token.lexeme == ">=")
    {
    	generateInstruction("GEQ",-1);
    	JUMPStack.push(instrTable.size());
    	generateInstruction("JMP0", -1);
    }
    match(token.lexeme);
    // part 3
    relational = 1;
//    std::cout << "INSTRUCTION" << instrTable[3].instr;
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
  if (token.lexeme == "+") {
    printRule("   <Expression'> ::= +|− <Term> <Expression'>");
    match(token.lexeme);
    Term();
    generateInstruction("A", -1);
    ExpressionPrime();
  } else if(token.lexeme == "-"){
	  printRule("   <Expression'> ::= +|− <Term> <Expression'>");
	  match(token.lexeme);
	  Term();
	  generateInstruction("S", -1);
	  ExpressionPrime();
  }   else {
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
    generateInstruction("M", -1);
    TermPrime();
  } else {
    printRule("   <Term'> ::= ε");
  }
}

// R34: <Factor> ::= - <Primary> | <Primary>
void Factor() {
  if (token.lexeme == "-") {

	// Check for non-variable integers
	if(!isdigit(token.lexeme[0]))
	{
		generateInstruction("PUSHM", getAddress(token.lexeme));
	}

	printRule("   <Factor> ::= - <Primary>");
    match("-");
    Primary();
  } else {
    printRule("   <Factor> ::= <Primary>");
	// Check for non-variable integers
	if(!isdigit(token.lexeme[0]))
	{
		generateInstruction("PUSHM", getAddress(token.lexeme));
	}
    Primary();
  }
}

// R35: <Primary> ::= identifier [ ( <IDs> ) ] | integer | ( <Expression>
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
	generateInstruction("PUSHI", stoi(token.lexeme));
    match("integer");
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



/*******************************************************************************
 ====================== PROJECT PART 3 FUNCTIONS ===============================
 ******************************************************************************/
// Pass variable to function and return the address of that variable
int getAddress(std::string variable)
{
	int address = -1000;

	if(!std::isdigit(variable[0]))
	{
		for(int i = 0; i < symbolTable.size(); i++)
		{
			if(symbolTable[i].id == variable)
			{
				address = symbolTable[i].address;
			}
		}

		if(address == -1000)
		{
			std::cout << "Error: variable \'" << variable << "\' not defined.";
		}
	}
	else
	{
		// chance of breaking program but work for things like i = i + 1
		address = stoi(variable);
	}

	return address;
}

// Uses getAddress() return for address param.
void generateInstruction(std::string instr, int address)
{
	Instr_Table_Item temp;
	temp.address = instrTable.size();
	temp.instr   = instr;

	// -1 stands for 'nil' so we dont need to
	if(address == -1)
	{
		temp.operand = -1;
	}
	else
	{
		temp.operand = address;
	}
	instrTable.push_back(temp);

	// Checks if this is the next instruction after a relational
	// because I couldnt find a way to push twice before relationals
	// so I just make a couple swaps in our vector to make it seem I did
	if(relational)
	{

		relational = 0;
	}
	return;
}

//
void backPatch(int instrAddress)
{
	std::cout << "TOP OF JUMPSTACK" << JUMPStack.top() << std::endl;
	int addr = JUMPStack.top();
	JUMPStack.pop();

	instrTable[addr].operand = instrAddress;
	return;
}
