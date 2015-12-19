#pragma once
#include "OcNode.h"
#include "Collider3D.h"

class OcTree
{
private:
	OcNode* root = nullptr;
public:
	OcTree(glm::vec3 c, glm::vec3 e);
	~OcTree();

	void print();
	bool collidesWith(Collider3D* other);
	void add(Collider3D* other);
};

