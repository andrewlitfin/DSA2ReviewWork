#pragma once
#include <glm\glm.hpp>
#include <iostream>

class Collider2D
{
public:
	glm::vec2 c, e; // Center and Halfwidth

	Collider2D(glm::vec2 c, glm::vec2 e);
	~Collider2D();

	void print();

	bool collidesWith(Collider2D* other);
};

extern std::ostream& operator<<(std::ostream& stream, glm::vec2& v);