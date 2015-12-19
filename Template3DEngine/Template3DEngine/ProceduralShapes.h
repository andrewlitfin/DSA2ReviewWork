#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <glew.h>
#include <glfw3.h>
#include <vector>

class ProceduralShapes
{
private:
	std::vector<GLfloat> vertices; // Acted upon by each 'f' position/texture[/normal] set
	std::vector<GLushort> elements; // Holds indices for each TRIANGLE, NOT QUAD.  DO NOT PUSH QUADS.

	void addQuad(glm::vec3 a, glm::vec2 uvA,
		glm::vec3 b, glm::vec2 uvB,
		glm::vec3 c, glm::vec2 uvC,
		glm::vec3 d, glm::vec2 uvD);
	void addTriangle(glm::vec3 a, glm::vec2 uvA,
		glm::vec3 c, glm::vec2 uvC,
		glm::vec3 b, glm::vec2 uvB);
	glm::vec3 getNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c);

	void makeCube();
	void makeCylinder(int nSides);
	void makeSphere(int iMax, int jMax);
	void makeBezierSurface(int uiMax, int viMax, std::vector<std::vector<glm::vec3>> k);

	void makeBezierSurfaceCaller();
	glm::vec3 bezierSurface(float u, float v, std::vector<std::vector<glm::vec3>> k);
	float bernsteinPolynomial(int i, int n, float u);
	float binomialCoefficient(int n, int k);

	glm::vec3 sphereV(float r, float theta, float phi);
public:
	enum primitive { cube, sphere, cylinder, bezier };

	ProceduralShapes(primitive type);
	~ProceduralShapes();

	std::vector<GLfloat> getVertices();
	std::vector<GLushort> getElements();
};

