#pragma once
#include "BinaryNode.h"
#include "Collider1D.h"

class BinaryTree
{
private:
	BinaryNode* root = nullptr;
public:
	BinaryTree(float c, float e);
	~BinaryTree();

	void print();
	bool collidesWith(Collider1D* other);
	void add(Collider1D* other);
};

