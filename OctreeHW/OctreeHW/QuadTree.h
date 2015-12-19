#pragma once
#include "QuadNode.h"
#include "Collider2D.h"

class QuadTree
{
private:
	QuadNode* root = nullptr;
public:
	QuadTree(glm::vec2 c, glm::vec2 e);
	~QuadTree();

	void print();
	bool collidesWith(Collider2D* other);
	void add(Collider2D* other);
};

