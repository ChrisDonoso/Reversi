#pragma once
#include "stdafx.h"


using namespace std;

struct Node
{
	int value;
	int alpha;
	int beta;
	
	Node *left;
	Node *right;
};

class BinaryTree
{
	public:
		BinaryTree();
		~BinaryTree();

		Node *insert(Node *tree, int value, int alpha, int beta);
		
		void destroyPath(Node *tree);

	private:
		Node *root;

};

