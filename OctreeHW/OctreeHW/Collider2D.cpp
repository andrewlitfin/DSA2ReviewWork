#include "Collider2D.h"



Collider2D::Collider2D(glm::vec2 c, glm::vec2 e)
	: c(c), e(e)
{
}

Collider2D::~Collider2D()
{
}

void Collider2D::print()
{
	std::cout << "Collider2D: c = " << c << "; e = " << e << std::endl;
}

bool Collider2D::collidesWith(Collider2D * other)
{
	// Two dimensional SAT on AABB
	if (fabsf(c.x - other->c.x) > e.x + other->e.x) return false;
	if (fabsf(c.y - other->c.y) > e.y + other->e.y) return false;
	return true; // No separating axis found, so they are colliding
}

std::ostream& operator<<(std::ostream& stream, glm::vec2& v)
{
	stream << "(" << v.x << ", " << v.y << ")";
	return stream;
}