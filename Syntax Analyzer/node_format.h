#ifndef SYNTAX_ANALYZER_NODE_FORMAT_H_
#define SYNTAX_ANALYZER_NODE_FORMAT_H_

#include <iostream>

// Each of these are a node in a binary tree
// l/r will be NULL if they have no children
struct Node
{
	std::string data;	 // Can be anything, used for data storage
	Node* left;   // Points to the address of the left child
	Node* middle; // Points to the address of the middle child
	Node* right;  // Points to the address of the right child
};





#endif /* SYNTAX_ANALYZER_NODE_FORMAT_H_ */
