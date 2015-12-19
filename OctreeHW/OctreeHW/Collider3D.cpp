#include "Collider3D.h"



Collider3D::Collider3D(glm::vec3 c, glm::vec3 e)
	: c(c), e(e)
{
}

Collider3D::~Collider3D()
{
}

void Collider3D::print()
{
	std::cout << "Collider3D: c = " << c << "; e = " << e << std::endl;
}

bool Collider3D::collidesWith(Collider3D * other)
{
	// SAT in 3D for AABB
	if (fabsf(c.x - other->c.x) > e.x + other->e.x) return false;
	if (fabsf(c.y - other->c.y) > e.y + other->e.y) return false;
	if (fabsf(c.z - other->c.z) > e.z + other->e.z) return false;
	return true;
}

std::ostream& operator<<(std::ostream& stream, glm::vec3& v)
{
	stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return stream;
}