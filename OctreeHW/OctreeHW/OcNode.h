#pragma once
#include "Collider3D.h"
#include <vector>
#include <string>
#include <iostream>
#include <glm\glm.hpp>

class OcNode
{
private:
	Collider3D binBox;
	int count = 0;
	static const int capacity = 4;
	int depth;
	static const int max_depth = 8;
	std::vector<Collider3D*> colliders = std::vector<Collider3D*>(capacity);
	bool isLeaf = true;
	OcNode* octant1 = nullptr; // Positive x, Positive y, Positive z
	OcNode* octant2 = nullptr; // Positive x, Positive y, Negative z
	OcNode* octant3 = nullptr; // Positive x, Negative y, Positive z
	OcNode* octant4 = nullptr; // Positive x, Negative y, Negative z
	OcNode* octant5 = nullptr; // Negative x, Positive y, Positive z
	OcNode* octant6 = nullptr; // Negative x, Positive y, Negative z
	OcNode* octant7 = nullptr; // Negative x, Negative y, Positive z
	OcNode* octant8 = nullptr; // Negative x, Negative y, Negative z

public:
	OcNode(glm::vec3 c, glm::vec3 e, int depth);
	~OcNode();

	void print(int tabStops);

	bool collidesWith(Collider3D* other);
	void add(Collider3D* other);
	void branch();
};

