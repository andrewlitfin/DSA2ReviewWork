#pragma once
#include "GameObject.h"

class Camera :
	public GameObject
{
	GLuint uniformCameraMatrixLocation;
	GLuint uniformEyeLocation;
public:
	Camera(GLuint shaderIndex);
	~Camera();

	void draw();
};

