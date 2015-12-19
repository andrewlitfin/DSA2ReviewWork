#include "QuadNode.h"



QuadNode::QuadNode(glm::vec2 c, glm::vec2 e, int depth)
	: binBox(Collider2D(c, e)), depth(depth)
{
}

QuadNode::~QuadNode()
{
	if (quadrant1 != nullptr) delete quadrant1;
	if (quadrant2 != nullptr) delete quadrant2;
	if (quadrant3 != nullptr) delete quadrant3;
	if (quadrant4 != nullptr) delete quadrant4;
}

void QuadNode::print(int tabStops)
{
	std::string printSep = "  ";

	for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
	std::cout << "QuadNode " << this << " information:" << std::endl;
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
		std::cout << "Node is a branch." << std::endl;
		for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
		std::cout << "Quadrant1 information of node " << this << ":" << std::endl;
		quadrant1->print(tabStops + 1);
		for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
		std::cout << "Quadrant2 information of node " << this << ":" << std::endl;
		quadrant2->print(tabStops + 1);
		for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
		std::cout << "Quadrant3 information of node " << this << ":" << std::endl;
		quadrant3->print(tabStops + 1);
		for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
		std::cout << "Quadrant4 information of node " << this << ":" << std::endl;
		quadrant4->print(tabStops + 1);
	}
}

bool QuadNode::collidesWith(Collider2D * other)
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
		if (quadrant1->collidesWith(other))
		{
			return true;
		}
		if (quadrant2->collidesWith(other))
		{
			return true;
		}
		if (quadrant3->collidesWith(other))
		{
			return true;
		}
		if (quadrant4->collidesWith(other))
		{
			return true;
		}
	}

	return false;
}

void QuadNode::add(Collider2D * other)
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
		quadrant1->add(other);
		quadrant2->add(other);
		quadrant3->add(other);
		quadrant4->add(other);
	}
}

void QuadNode::branch()
{
	isLeaf = false;

	float qwx = binBox.e.x / 2.0f;
	float qwy = binBox.e.y / 2.0f;
	quadrant1 = new QuadNode(glm::vec2(binBox.c.x + qwx, binBox.c.y + qwy), glm::vec2(qwx, qwy), depth + 1);
	quadrant2 = new QuadNode(glm::vec2(binBox.c.x - qwx, binBox.c.y + qwy), glm::vec2(qwx, qwy), depth + 1);
	quadrant3 = new QuadNode(glm::vec2(binBox.c.x - qwx, binBox.c.y - qwy), glm::vec2(qwx, qwy), depth + 1);
	quadrant4 = new QuadNode(glm::vec2(binBox.c.x + qwx, binBox.c.y - qwy), glm::vec2(qwx, qwy), depth + 1);

	for (int i = 0; i < count; i++)
	{
		quadrant1->add(colliders[i]);
		quadrant2->add(colliders[i]);
		quadrant3->add(colliders[i]);
		quadrant4->add(colliders[i]);
		colliders[i] = nullptr;
	}

	count = 0;
}
