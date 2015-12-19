#include "GameObject.h"



GameObject::GameObject(Mesh * mesh, GLuint shaderIndex)
	: mesh(mesh), shaderIndex(shaderIndex)
{
	uniformWorldMatrixLocation = glGetUniformLocation(shaderIndex, "worldMatrix");
}

GameObject::~GameObject()
{
	if (mesh != nullptr)
	{
		delete mesh;
	}
}

void GameObject::update(float dt)
{
	//// Apply gravity
	//netForce += glm::vec3(0, -9.8f, 0);
	//// Apply drag
	//netForce += velocity * -0.2f;

	// Euler integration for position function
	velocity += dt * netForce / mass;
	location += dt * velocity;

	// Increment angle of rotation
	rAngle += angularVelocity * dt;

	// Reset forces to zero
	netForce = glm::vec3();
}

void GameObject::draw()
{
	if (mesh != nullptr)
	{
		glm::mat4 worldMatrix = glm::translate(location) * glm::scale(scale) * glm::rotate(rAngle, rAxis);
		glProgramUniformMatrix4fv(shaderIndex, uniformWorldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
		mesh->draw();
	}
}

void GameObject::setScale(glm::vec3 newscale)
{
	scale = newscale;
}

void GameObject::applyForce(glm::vec3 force)
{
	netForce += force;
}

void GameObject::setLocation(glm::vec3 newLocation)
{
	location = newLocation;
}

glm::vec3 GameObject::getLocation()
{
	return location;
}

void GameObject::setVelocity(glm::vec3 newVelocity)
{
	velocity = newVelocity;
}

glm::vec3 GameObject::getVelocity()
{
	return velocity;
}

void GameObject::setAngularVelocity(float newAngularVelocity)
{
	angularVelocity = newAngularVelocity;
}
