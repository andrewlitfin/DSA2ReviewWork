#pragma once
#include <glm\glm.hpp>
#include <iostream>

class Collider3D
{
public:
	glm::vec3 c, e; // Center and Halfwidth

	Collider3D(glm::vec3 c, glm::vec3 e);
	~Collider3D();

	void print();

	bool collidesWith(Collider3D* other);
};

extern std::ostream& operator<<(std::ostream& stream, glm::vec3& v);