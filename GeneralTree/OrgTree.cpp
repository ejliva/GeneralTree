#include "stdafx.h"
#include "OrgTree.h"
#include <iostream>
#include <string>
#include <fstream>
#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL

using namespace std;


OrgTree::OrgTree()
{
	count = 0;
}

//This is the parameterized constructor
OrgTree::OrgTree(string newTitle, string newName)
{
	title = newTitle;
	name = newName;
}

OrgTree::~OrgTree()
{
	delete root;
}

//This creates a root node for the tree.
//if the there already has a root, the entire tree becomes a subtree of the new root.
//the asymptotic run time of this function is in Θ(1) notation, for a tree of size n
void OrgTree::addRoot(string title, string name)
{
	if (root == NULL) {
		TREENODEPTR newNode = new TreeNode;
		newNode->title = title;
		newNode->name = name;
		newNode->leftChild = nullptr;
		newNode->rightSibling = nullptr;
		newNode->parent = nullptr;
		root = newNode;
	}
	else {
		TREENODEPTR newRoot = new TreeNode;
		newRoot->title = title;
		newRoot->name = name;
		newRoot->leftChild = root;
		newRoot->rightSibling = nullptr;
		newRoot->parent = nullptr;
		root->parent = newRoot;
		root = newRoot;
	}
	count++;	//track the number of employees.
}

//This returns the number of employees in the tree
//the asymptotic run time of this function is in Θ(1) notation, for a tree of size n
unsigned int OrgTree::getSize()
{
	return count;
}

//Returns a pointer to the root node in the tree.
//the asymptotic run time of this function is in Θ(1) notation, for a tree of size n
OrgTree::TREENODEPTR OrgTree::getRoot()
{
	return root;
}

//This returns the left child of the node that is passed to function
//this returns TREENULLPTR if the node has no children.
//the asymptotic run time of this function is in Θ(1) notation, for a tree of size n
OrgTree::TREENODEPTR OrgTree::leftmostChild(TREENODEPTR node)
{
	if (node->leftChild == TREENULLPTR) {
		return TREENULLPTR;
	}
	else
	{
		return 	node->leftChild;
	}
}

//This returns a pointer to the right sibling of the node passed to the function.
//if no right sibling return TREENULLPTR
//the asymptotic run time of this function is in Θ(1) notation, for a tree of size n
OrgTree::TREENODEPTR OrgTree::rightSibling(TREENODEPTR node)
{
	if (node->rightSibling == TREENULLPTR) {
		return TREENULLPTR;
	}
	else
	{
		return node->rightSibling;
	}
}

//print out the subtree starting at the node pointed to by subTreeRoot.
//This function should use indentation to show the tree structure
//the asymptotic run time of this function is in Θ(n) notation, for a tree of size n
void OrgTree::printSubTree(TREENODEPTR subTreeRoot)
{
	preOrder(subTreeRoot);
}

//this is the preOrder traversal for binary tree
//the asymptotic run time of this function is in Θ(n) notation, for a tree of size n
void OrgTree::preOrder(TREENODEPTR current)
{
	if (current == TREENULLPTR)
		return;
	cout << current->title << ", " << current->title + "\n"; // display the current node
	preOrder(current->leftChild);	// display the left subtree
	preOrder(current->rightSibling);          // display the right subtree
}

//this function is a pre order traversal 
//the asymptotic run time of this function is in Θ(1) notation, for a tree of size n
void OrgTree::writePreOrder(TREENODEPTR current, ostream &file) {
	if (!current) {
		file << ")\n";
	}
	else {
		file << current->title << ", " << current->title + "\n";
		writePreOrder(current->leftChild, file);
		writePreOrder(current->rightSibling, file);
	}
}

//this is a find helper function.
//takes two treenodeptr and string
//the asymptotic run time of this function is in Θ(n) notation, for a tree of size n
OrgTree::TREENODEPTR OrgTree::find(TREENODEPTR current, TREENODEPTR ptr, string title) {
	if (current->title == title) {
		ptr = current;	//s
	}
	for (TREENODEPTR node = current->leftChild; node != NULL; node = node->rightSibling) {
		ptr = find(node, ptr, title);
	}
	return ptr;
}
//returns a TREENODEPTR to the node listing the given title(exact string match with the title string in a TreeNode object).
//If the title is not found, the function should return TREENULLPTR.For simplicity, you may assume that all titles in the company are unique.
//the asymptotic run time of this function is in Θ(n) notation, for a tree of size n
OrgTree::TREENODEPTR OrgTree::find(string title)
{
	return find(root, TREENULLPTR, title);

}

//reads an organization tree from a file. 
//The file will contain one tree node per line, except for lines containing only ')' characters, which mark the ends of subtrees
//If the file is found and read successfully, this function should return true. 
//If the file is not found or the file is improperly formatted, the function should return false.
//the asymptotic run time of this function is in Θ(n) notation, for a tree of size n
bool OrgTree::read(string filename)
{
	string title;
	string name;
	ifstream myfile(filename);

	if (!myfile.is_open()) {
		cerr << "Couldn't open file!" << endl;
		system("cd");
		return true;
	}
	else {
		while (!myfile.eof()) {
			if (myfile.peek() == '#') {
				myfile.ignore(256, '\n');
			}
			else {
				getline(myfile, title, ',');
				getline(myfile, name, '\n');
				cout << title << name << endl;
			}
		}
	}
	return false;
}

//OrgTree::TREENODEPTR OrgTree::readTree(ifstream &file) {
//	string newTitle, newName, junk;
//	if (file.peek() == ')') {
//		return TREENULLPTR;
//	}
//	getline(file, newTitle, ',');
//	getline(file, newName);
//	TREENODEPTR subroot = new TreeNode();
//	subroot->title = newTitle;
//	subroot->name = newName;
//	while (file.peek() != ')') {
//		TREENODEPTR ptr = readTree(file);
//		if (ptr != TREENULLPTR)
//		{
//			addChild(ptr, subroot);
//		}
//	}
//}


//write out the OrgTree to a file, using the same file format described in the read() function above.
//the asymptotic run time of this function is in Θ(n) notation, for a tree of size n
void OrgTree::write(string filename)
{
	ofstream myFile(filename);
	if (!myFile.is_open()) {
		cerr << "Couldn't open file!" << endl;
		system("cd");
	}

	writePreOrder(root, myFile);

}

//This function hires a employee and should be added as the last child of the node pointed to by TREENODEPTR.
//the asymptotic run time of this function is in Θ(n) notation, for a tree of size n
void OrgTree::hire(TREENODEPTR employee, string newTitle, string newName)
{

	TREENODEPTR newNode = new TreeNode;
	newNode->title = newTitle;
	newNode->name = newName;
	newNode->leftChild = TREENULLPTR;
	newNode->rightSibling = TREENULLPTR;
	newNode->parent = employee;

	if (employee->leftChild == NULL) {
		employee->leftChild = newNode;
	}
	else {
		TREENODEPTR child = employee->leftChild;
		while (child->rightSibling != NULL) {
			child = child->rightSibling;
		}
		child->rightSibling = newNode;
	}
	count++;
}
//This fires the employee who's title matches the argument to this function.
//If the title is found the employee's node in the tree is deleted and the function returns true
//All employees of the fired employee now work directly for the fired employee's boss. 
//If no match is found the function returns false
//If the formerTitle matches the root node, the function should return false.
//bool OrgTree::fire(string formerTitle) {
//	//Declare variables
//	TREENODEPTR current = new TreeNode;
//	TREENODEPTR child = new TreeNode;
//	TREENODEPTR parent = new TreeNode;
//
//	if (root->title == formerTitle) {
//		return false;
//	}
//
//	current = find(formerTitle);
//
//	if (fire == TREENULLPTR) {
//		return false;
//	}
//
//	if (current->leftChild != TREENULLPTR) {
//		child = current->leftChild;
//		parent = current->parent;
//
//		parent->leftChild = child;
//
//		while (child->rightSibling != TREENULLPTR) {
//			child->parent = current->parent;
//			child = child->rightSibling;
//		}
//		child->parent = current->parent;
//	}
//	return true;
//}