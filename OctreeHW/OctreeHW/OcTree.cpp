#include "OcTree.h"



OcTree::OcTree(glm::vec3 c, glm::vec3 e)
	: root(new OcNode(c, e, 0))
{
}

OcTree::~OcTree()
{
	if (root != nullptr)
	{
		delete root;
	}
}

void OcTree::print()
{
	std::cout << "Collider Oc Tree: " << std::endl;
	root->print(0);
}

bool OcTree::collidesWith(Collider3D * other)
{
	return root->collidesWith(other);
}

void OcTree::add(Collider3D * other)
{
	root->add(other);
}
