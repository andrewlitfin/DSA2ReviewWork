#include "BinaryTree.h"



BinaryTree::BinaryTree(float c, float e)
	: root(new BinaryNode(c, e, 0))
{
}

BinaryTree::~BinaryTree()
{
	if (root != nullptr)
	{
		delete root;
	}
}

void BinaryTree::print()
{
	std::cout << "Collider Binary Tree: " << std::endl;
	root->print(0);
}

bool BinaryTree::collidesWith(Collider1D * other)
{
	return root->collidesWith(other);
}

void BinaryTree::add(Collider1D * other)
{
	root->add(other);
}
