#include "OcNode.h"



OcNode::OcNode(glm::vec3 c, glm::vec3 e, int depth)
	: binBox(Collider3D(c, e)), depth(depth)
{
}

OcNode::~OcNode()
{
	if (octant1 != nullptr) delete octant1;
	if (octant2 != nullptr) delete octant2;
	if (octant3 != nullptr) delete octant3;
	if (octant4 != nullptr) delete octant4;
	if (octant5 != nullptr) delete octant5;
	if (octant6 != nullptr) delete octant6;
	if (octant7 != nullptr) delete octant7;
	if (octant8 != nullptr) delete octant8;
}

void OcNode::print(int tabStops)
{
	std::string printSep = "  ";

	for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
	std::cout << "OcNode " << this << " information:" << std::endl;
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
		std::cout << "Octant1 information of node " << this << ":" << std::endl;
		octant1->print(tabStops + 1);
		for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
		std::cout << "Octant2 information of node " << this << ":" << std::endl;
		octant2->print(tabStops + 1);
		for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
		std::cout << "Octant3 information of node " << this << ":" << std::endl;
		octant3->print(tabStops + 1);
		for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
		std::cout << "Octant4 information of node " << this << ":" << std::endl;
		octant4->print(tabStops + 1);
		for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
		std::cout << "Octant5 information of node " << this << ":" << std::endl;
		octant5->print(tabStops + 1);
		for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
		std::cout << "Octant6 information of node " << this << ":" << std::endl;
		octant6->print(tabStops + 1);
		for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
		std::cout << "Octant7 information of node " << this << ":" << std::endl;
		octant7->print(tabStops + 1);
		for (int i = 0; i < tabStops; i++) std::cout << printSep.c_str();
		std::cout << "Octant8 information of node " << this << ":" << std::endl;
		octant8->print(tabStops + 1);
	}
}

bool OcNode::collidesWith(Collider3D * other)
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
		if (octant1->collidesWith(other))
		{
			return true;
		}
		if (octant2->collidesWith(other))
		{
			return true;
		}
		if (octant3->collidesWith(other))
		{
			return true;
		}
		if (octant4->collidesWith(other))
		{
			return true;
		}
		if (octant5->collidesWith(other))
		{
			return true;
		}
		if (octant6->collidesWith(other))
		{
			return true;
		}
		if (octant7->collidesWith(other))
		{
			return true;
		}
		if (octant8->collidesWith(other))
		{
			return true;
		}
	}

	return false;
}

void OcNode::add(Collider3D * other)
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
		octant1->add(other);
		octant2->add(other);
		octant3->add(other);
		octant4->add(other);
		octant5->add(other);
		octant6->add(other);
		octant7->add(other);
		octant8->add(other);
	}
}

void OcNode::branch()
{
	isLeaf = false;

	float qwx = binBox.e.x / 2.0f;
	float qwy = binBox.e.y / 2.0f;
	float qwz = binBox.e.z / 2.0f;
	octant1 = new OcNode(glm::vec3(binBox.c.x + qwx, binBox.c.y + qwy, binBox.c.z + qwz), glm::vec3(qwx, qwy, qwz), depth + 1);
	octant2 = new OcNode(glm::vec3(binBox.c.x + qwx, binBox.c.y + qwy, binBox.c.z - qwz), glm::vec3(qwx, qwy, qwz), depth + 1);
	octant3 = new OcNode(glm::vec3(binBox.c.x + qwx, binBox.c.y - qwy, binBox.c.z + qwz), glm::vec3(qwx, qwy, qwz), depth + 1);
	octant4 = new OcNode(glm::vec3(binBox.c.x + qwx, binBox.c.y - qwy, binBox.c.z - qwz), glm::vec3(qwx, qwy, qwz), depth + 1);
	octant5 = new OcNode(glm::vec3(binBox.c.x - qwx, binBox.c.y + qwy, binBox.c.z + qwz), glm::vec3(qwx, qwy, qwz), depth + 1);
	octant6 = new OcNode(glm::vec3(binBox.c.x - qwx, binBox.c.y + qwy, binBox.c.z - qwz), glm::vec3(qwx, qwy, qwz), depth + 1);
	octant7 = new OcNode(glm::vec3(binBox.c.x - qwx, binBox.c.y - qwy, binBox.c.z + qwz), glm::vec3(qwx, qwy, qwz), depth + 1);
	octant8 = new OcNode(glm::vec3(binBox.c.x - qwx, binBox.c.y - qwy, binBox.c.z - qwz), glm::vec3(qwx, qwy, qwz), depth + 1);

	for (int i = 0; i < count; i++)
	{
		octant1->add(colliders[i]);
		octant2->add(colliders[i]);
		octant3->add(colliders[i]);
		octant4->add(colliders[i]);
		octant5->add(colliders[i]);
		octant6->add(colliders[i]);
		octant7->add(colliders[i]);
		octant8->add(colliders[i]);
		colliders[i] = nullptr;
	}

	count = 0;
}
