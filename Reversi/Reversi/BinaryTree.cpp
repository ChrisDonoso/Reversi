#include "stdafx.h"
#include "BinaryTree.h"


BinaryTree::BinaryTree()
{
	root = NULL;
}


BinaryTree::~BinaryTree()
{
}


//Review and discuss the parameters and how they are going to be created.
Node * BinaryTree::insert(Node * tree, int value, int alpha, int beta)
{
	//Review
	if (tree == NULL)
	{
		tree = new Node();
		return insert(tree, value, alpha, beta);
	}

	if (value < tree->value)
		tree->left = insert(tree->left, value, alpha, beta);

	else if (value > tree->value)
		tree->right = insert(tree->right, value, alpha, beta);

	return tree;
}

void BinaryTree::destroyPath(Node * tree)
{
	if (tree != NULL)
	{
		destroyPath(tree->left);
		destroyPath(tree->right);
		delete tree;
	}
}
