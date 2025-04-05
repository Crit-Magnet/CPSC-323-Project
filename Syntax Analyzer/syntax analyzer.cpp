#include <iomanip>
#include <string>
#include <sstream>
#include "../Lexical Analyzer/lexer.h"
#include "syntax_analyzer.h"



// Initializer for new Nodes going onto the tree
Node* getNewNode(std::string data)
{
	Node* newNode   = new Node();
	newNode->data   = data;
	newNode->left   = NULL;
	newNode->middle = NULL;
	newNode->right  = NULL;
	return newNode;
}


Node* Insert(Node* root, std::string data)
{
	if(root == NULL) // if tree is empty
	{
		root = getNewNode(data);
	}
//	else if(root->data >= data)
//	{
//		// Since data being added is < than its parent/root, we add it to the
//		// left, resulting in the parent's left address being assigned the
//		// address of the new Node
//		root->left = Insert(root->left, data);
//	}
	else
	{
		// Since data being added is < than its parent/root, we add it to the
		// right, resulting in the parent's right address being assigned the
		// address of the new Node
		root->right = Insert(root->right, data);
	}

	return root;
}

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
