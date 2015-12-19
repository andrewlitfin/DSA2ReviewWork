#pragma once
#include <glm\glm.hpp>
#include <glew.h>
#include <glfw3.h>
#include <SOIL.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

#include "ProceduralShapes.h"

class Mesh
{
private:
	GLuint vaoIndex, vboIndex;
	GLuint textureID = 0;
	int numElements;

	// There exists common code between different ways of setting up a Mesh
	void initBuffers(const std::vector<GLfloat>& vertices, const std::vector<GLushort>& elements);
public:
	void loadTexture(std::string textureFilePath);
	Mesh(); // Default constructor makes a Tetrahedron with no texture
	Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLushort>& elements, std::string textureFilePath); // Takes vertices and elements
	Mesh(std::string fileName, std::string textureFilePath); // Takes a filename to an obj and loads it
	Mesh(ProceduralShapes::primitive type); // Procedural model, no texture

	~Mesh();

	void draw();
};

