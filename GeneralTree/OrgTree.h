#pragma once
#include <string>
#include <iostream>
#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL

using namespace std;

class OrgTree
{
private:
	struct TreeNode {
		string title;
		string name;
		TREENODEPTR parent;
		TREENODEPTR rightSibling;
		TREENODEPTR leftChild;

	};
	TREENODEPTR root;
	string title;
	string name;
	int count;

public:
	OrgTree();

	OrgTree(string, string);

	~OrgTree();

	void addRoot(string, string);

	unsigned int getSize();

	TREENODEPTR getRoot();

	TREENODEPTR leftmostChild(TREENODEPTR);

	TREENODEPTR rightSibling(TREENODEPTR);

	void printSubTree(TREENODEPTR);

	void preOrder(TREENODEPTR);

	void writePreOrder(TREENODEPTR, ostream&);

	OrgTree::TREENODEPTR find(TREENODEPTR, TREENODEPTR, string);

	TREENODEPTR find(string);

	TREENODEPTR addChild(TREENODEPTR newNode, TREENODEPTR parent);

	bool read(string);

	OrgTree::TREENODEPTR readTree(ifstream & file);

	void write(string);

	void hire(TREENODEPTR, string, string);

	bool fire(string);

};

