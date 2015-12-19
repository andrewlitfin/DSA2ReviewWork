#pragma once
#include "Mesh.h"
#include <glm\gtx\transform.hpp>

class GameObject
{
protected:
	Mesh* mesh = nullptr;

	glm::vec3 location = glm::vec3(0);
	glm::vec3 scale = glm::vec3(1);
	float rAngle = 0;
	glm::vec3 rAxis = glm::vec3(0, 1, 0);
	glm::vec3 velocity = glm::vec3(0);
	float angularVelocity = 0;
	glm::vec3 netForce = glm::vec3(0);
	float mass = 1;

	GLuint shaderIndex;
	GLuint uniformWorldMatrixLocation;
public:
	GameObject(Mesh* mesh, GLuint shaderIndex);
	~GameObject();

	void update(float dt);
	void draw();

	void setScale(glm::vec3 newscale);

	void applyForce(glm::vec3 force);

	void setLocation(glm::vec3 newLocation);
	glm::vec3 getLocation();

	void setVelocity(glm::vec3 newVelocity);
	glm::vec3 getVelocity();

	void setAngularVelocity(float newAngularVelocity);
};

