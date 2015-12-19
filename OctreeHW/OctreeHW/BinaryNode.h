#pragma once
#include "Collider1D.h"
#include <vector>
#include <string>
#include <iostream>

class BinaryNode
{
private:
	Collider1D binBox;
	int count = 0;
	static const int capacity = 4;
	int depth;
	static const int max_depth = 8;
	std::vector<Collider1D*> colliders = std::vector<Collider1D*>(capacity);
	bool isLeaf = true;
	BinaryNode* leftChild = nullptr;
	BinaryNode* rightChild = nullptr;

public:
	BinaryNode(float c, float e, int depth);
	~BinaryNode();

	void print(int tabStops);

	bool collidesWith(Collider1D* other);
	void add(Collider1D* other);
	void branch();
};

