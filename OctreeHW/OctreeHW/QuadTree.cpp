#include "QuadTree.h"



QuadTree::QuadTree(glm::vec2 c, glm::vec2 e)
	: root(new QuadNode(c, e, 0))
{
}

QuadTree::~QuadTree()
{
	if (root != nullptr)
	{
		delete root;
	}
}

void QuadTree::print()
{
	std::cout << "Collider Quad Tree: " << std::endl;
	root->print(0);
}

bool QuadTree::collidesWith(Collider2D * other)
{
	return root->collidesWith(other);
}

void QuadTree::add(Collider2D * other)
{
	root->add(other);
}
