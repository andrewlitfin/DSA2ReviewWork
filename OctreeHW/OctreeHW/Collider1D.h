#pragma once
#include <iostream>

class Collider1D
{
public:
	float c, e; // Center and Halfwidth

	Collider1D(float c, float e);
	~Collider1D();

	void print();

	bool collidesWith(Collider1D* other);
};

