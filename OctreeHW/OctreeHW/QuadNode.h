#pragma once
#include "Collider2D.h"
#include <vector>
#include <string>
#include <iostream>
#include <glm\glm.hpp>

class QuadNode
{
private:
	Collider2D binBox;
	int count = 0;
	static const int capacity = 4;
	int depth;
	static const int max_depth = 8;
	std::vector<Collider2D*> colliders = std::vector<Collider2D*>(capacity);
	bool isLeaf = true;
	QuadNode* quadrant1 = nullptr; // Positive x, Positive y
	QuadNode* quadrant2 = nullptr; // Negative x, Positive y
	QuadNode* quadrant3 = nullptr; // Negative x, Negative y
	QuadNode* quadrant4 = nullptr; // Positive x, Negative y

public:
	QuadNode(glm::vec2 c, glm::vec2 e, int depth);
	~QuadNode();

	void print(int tabStops);

	bool collidesWith(Collider2D* other);
	void add(Collider2D* other);
	void branch();
};

