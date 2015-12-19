#include "BinaryNode.h"



BinaryNode::BinaryNode(float c, float e, int depth) 
	: binBox(Collider1D(c, e)), depth(depth)
{
}


BinaryNode::~BinaryNode()
{
	if (rightChild != nullptr)
	{
		delete rightChild;
	}
	if (leftChild != nullptr)
	{
		delete leftChild;
	}
}

void BinaryNode::print(int tabStops)
{
	std::string printSep = "  ";

	for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
	std::cout << "BinaryNode " << this << " information:" << std::endl;
	for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
	std::cout << "BinBox: "; binBox.print();

	if (isLeaf)
	{
		for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
		std::cout << "Node is a leaf, and ";
		if (count == 0)
		{
			std::cout << "contains no colliders." << std::endl;
		}
		else if (count == 1)
		{
			std::cout << "contains collider " << colliders[0] << "." << std::endl;
		}
		else
		{
			std::cout << "contains colliders ";
			for (int i = 0; i < count - 1; i++) std::cout << colliders[i] << ((count != 2) ? ", " : " ");
			std::cout << "and " << colliders[count - 1] << "." << std::endl;
		}
	}
	else
	{
		for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
		std::cout << "Node is a branch.";
		for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
		std::cout << "RightChild information of node " << this << ":" << std::endl;
		rightChild->print(tabStops + 1);
		for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
		std::cout << "LeftChild information of node " << this << ":" << std::endl;
		leftChild->print(tabStops + 1);
	}
}

bool BinaryNode::collidesWith(Collider1D* other)
{
	if (!binBox.collidesWith(other))
	{
		return false;
	}

	if (isLeaf)
	{
		for (int i = 0; i < count; i++)
		{
			if (colliders[i]->collidesWith(other))
			{
				return true;
			}
		}
	}
	else
	{
		if (rightChild->collidesWith(other))
		{
			return true;
		}
		if (leftChild->collidesWith(other))
		{
			return true;
		}
	}

	return false;
}

void BinaryNode::add(Collider1D* other)
{
	// cull colliders that don't collide with the node
	if (!binBox.collidesWith(other))
	{
		return;
	}

	if (count >= capacity && depth < max_depth)
	{
		branch();
	}

	if (isLeaf)
	{
		if (count < capacity)
		{
			colliders[count] = other;
			count++;
		}
		else
		{
			colliders.push_back(other);
			count++;
		}
	}
	else
	{
		rightChild->add(other);
		leftChild->add(other);
	}
}

void BinaryNode::branch()
{
	isLeaf = false;

	float qw = binBox.e / 2.0f;
	leftChild = new BinaryNode(binBox.c - qw, qw, depth + 1);
	rightChild = new BinaryNode(binBox.c + qw, qw, depth + 1);

	for (int i = 0; i < count; i++)
	{
		leftChild->add(colliders[i]);
		rightChild->add(colliders[i]);
		colliders[i] = nullptr;
	}

	count = 0;
}
