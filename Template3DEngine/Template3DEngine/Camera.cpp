#include "Camera.h"



Camera::Camera(GLuint shaderIndex)
	: GameObject(nullptr, shaderIndex)
{
	uniformCameraMatrixLocation = glGetUniformLocation(shaderIndex, "cameraMatrix");
	uniformEyeLocation = glGetUniformLocation(shaderIndex, "eye");
}


Camera::~Camera()
{
}

void Camera::draw()
{
	glm::mat4 cameraMatrix = glm::perspective(
		glm::pi<float>() * 0.4f, 800.0f / 600.0f, 0.01f, 1000.0f
		) * glm::lookAt(location, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glUniformMatrix4fv(uniformCameraMatrixLocation, 1, GL_FALSE, &cameraMatrix[0][0]);
	glUniform3fv(uniformEyeLocation, 1, &location[0]);
}
