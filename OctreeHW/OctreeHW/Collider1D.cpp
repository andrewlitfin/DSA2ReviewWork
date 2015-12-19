#include "Collider1D.h"



Collider1D::Collider1D(float c, float e) 
	: c(c), e(e)
{
}

Collider1D::~Collider1D()
{
}

void Collider1D::print()
{
	std::cout << "Collider1D: c = " << c << "; e = " << e << std::endl;
}

bool Collider1D::collidesWith(Collider1D * other)
{
	return fabsf(c - other->c) < e + other->e;
}
