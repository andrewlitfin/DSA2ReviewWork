#include "ProceduralShapes.h"



void ProceduralShapes::addQuad(glm::vec3 a, glm::vec2 uvA, glm::vec3 b, glm::vec2 uvB, glm::vec3 c, glm::vec2 uvC, glm::vec3 d, glm::vec2 uvD)
{
	// Triangle 1
	addTriangle(a, uvA, b, uvB, c, uvC);

	// Triangle 2
	addTriangle(d, uvD, c, uvC, b, uvB);
}

void ProceduralShapes::addTriangle(glm::vec3 a, glm::vec2 uvA, glm::vec3 b, glm::vec2 uvB, glm::vec3 c, glm::vec2 uvC)
{
	// use the same normal across all three triangle points
	glm::vec3 normal = getNormal(a, b, c);

	// Push A
	vertices.push_back(a.x);
	vertices.push_back(a.y);
	vertices.push_back(a.z);
	vertices.push_back(uvA.x);
	vertices.push_back(uvA.y);
	vertices.push_back(normal.x);
	vertices.push_back(normal.y);
	vertices.push_back(normal.z);
	elements.push_back((GLushort)elements.size());

	// Push B
	vertices.push_back(b.x);
	vertices.push_back(b.y);
	vertices.push_back(b.z);
	vertices.push_back(uvB.x);
	vertices.push_back(uvB.y);
	vertices.push_back(normal.x);
	vertices.push_back(normal.y);
	vertices.push_back(normal.z);
	elements.push_back((GLushort)elements.size());

	// Push C
	vertices.push_back(c.x);
	vertices.push_back(c.y);
	vertices.push_back(c.z);
	vertices.push_back(uvC.x);
	vertices.push_back(uvC.y);
	vertices.push_back(normal.x);
	vertices.push_back(normal.y);
	vertices.push_back(normal.z);
	elements.push_back((GLushort)elements.size());

}

glm::vec3 ProceduralShapes::getNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	glm::vec3 vAC = c - a;
	glm::vec3 vAB = b - a;
	return glm::normalize(glm::cross(vAB, vAC));
}

void ProceduralShapes::makeCube()
{
	std::vector<glm::vec3> pos = {
		glm::vec3( 0.5f, 0.5f, 0.5f), glm::vec3( 0.5f, 0.5f, -0.5f), glm::vec3( 0.5f, -0.5f, 0.5f), glm::vec3( 0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, -0.5f)
	};
	std::vector<glm::vec2> uvs = {
		glm::vec2(0.25f, 0.0f), glm::vec2(0.5f, 0.0f),
		glm::vec2(0, 0.25f), glm::vec2(0.25f, 0.25f), glm::vec2(0.5f, 0.25f), glm::vec2(0.75f, 0.25f), glm::vec2(1.0f, 0.25f),
		glm::vec2(0, 0.5f), glm::vec2(0.25f, 0.5f), glm::vec2(0.5f, 0.5f), glm::vec2(0.75f, 0.5f), glm::vec2(1.0f, 0.5f),
		glm::vec2(0.25f, 0.75f), glm::vec2(0.5f, 0.75f)
	};

	// Top
	addQuad(pos[5], uvs[0], pos[1], uvs[1], pos[4], uvs[3], pos[0], uvs[4]);

	// Left
	addQuad(pos[5], uvs[2], pos[4], uvs[3], pos[7], uvs[7], pos[6], uvs[8]);

	// Front
	addQuad(pos[4], uvs[3], pos[0], uvs[4], pos[6], uvs[8], pos[2], uvs[9]);

	// Right
	addQuad(pos[0], uvs[4], pos[1], uvs[5], pos[2], uvs[9], pos[3], uvs[10]);

	// Back
	addQuad(pos[1], uvs[5], pos[5], uvs[6], pos[3], uvs[10], pos[7], uvs[11]);

	// Bottom
	addQuad(pos[6], uvs[8], pos[2], uvs[9], pos[7], uvs[12], pos[3], uvs[13]);
}

void ProceduralShapes::makeCylinder(int nSides)
{
	// We use the following equation to define each vertex:
	// x = (1/2)sin(theta)
	// y = +/- 0.5
	// z = (1/2)cos(theta)
	// such are the oddities that arise when dealing with the xz plane

	float dTheta = glm::two_pi<float>() / (float)nSides;
	glm::vec3 zDisp = glm::vec3(0.0f, 0.5f, 0.0f);
	glm::vec2 topUVc = glm::vec2(0.25f, 0.25f);
	glm::vec2 botUVc = glm::vec2(0.75f, 0.25f);

	for (int i = 0; i < nSides; i++)
	{
		float theta = (float)i * dTheta;

		// Make upper disk
		glm::vec3 a = glm::vec3(0.5f * sinf(theta), 0.5f, 0.5f * cosf(theta));
		glm::vec3 b = glm::vec3(0.5f * sinf(theta + dTheta), 0.5f, 0.5f * cosf(theta + dTheta));
		glm::vec2 uvA1 = topUVc + glm::vec2(a.x, a.z) / 2.0f;
		glm::vec2 uvB1 = topUVc + glm::vec2(b.x, b.z) / 2.0f;
		addTriangle(a, uvA1, b, uvB1, zDisp, topUVc);

		// Make sides
		glm::vec3 c = a;
		c.y *= -1;
		glm::vec3 d = b;
		d.y *= -1;
		glm::vec2 uvA2 = glm::vec2((float)i / (float)nSides, 0.5f);
		glm::vec2 uvB2 = glm::vec2((float)(i + 1) / (float)nSides, 0.5f);
		glm::vec2 uvC2 = glm::vec2((float)i / (float)nSides, 1.0f);
		glm::vec2 uvD2 = glm::vec2((float)(i + 1) / (float)nSides, 1.0f);
		addQuad(a, uvA2, b, uvB2, c, uvC2, d, uvD2);

		// Make lower disk
		glm::vec2 uvC1 = botUVc + glm::vec2(c.x, c.z) / 2.0f;
		glm::vec2 uvD1 = botUVc + glm::vec2(d.x, d.z) / 2.0f;
		addTriangle(d, uvD1, c, uvC1, -zDisp, botUVc);
	}
}

void ProceduralShapes::makeSphere(int iMax, int jMax)
{
	float dTheta = glm::two_pi<float>() / (float)iMax;
	float dPhi = glm::pi<float>() / (float)jMax;

	for (int i = 0; i < iMax; i++)
	{
		for (int j = 0; j < jMax; j++)
		{
			float theta = i * dTheta;
			float phi = j * dPhi;

			glm::vec3 a = sphereV(0.5f, theta, phi);
			glm::vec2 uvA = glm::vec2((float)i / (float)iMax, (float)j / (float)jMax);
			glm::vec3 b = sphereV(0.5f, theta + dTheta, phi);
			glm::vec2 uvB = glm::vec2((float)(i + 1) / (float)iMax, (float)j / (float)jMax);
			glm::vec3 c = sphereV(0.5f, theta, phi + dPhi);
			glm::vec2 uvC = glm::vec2((float)i / (float)iMax, (float)(j + 1) / (float)jMax);
			glm::vec3 d = sphereV(0.5f, theta + dTheta, phi + dPhi);
			glm::vec2 uvD = glm::vec2((float)(i + 1) / (float)iMax, (float)(j + 1) / (float)jMax);

			addQuad(a, uvA, b, uvB, c, uvC, d, uvD);
		}
	}
}

void ProceduralShapes::makeBezierSurface(int uiMax, int viMax, std::vector<std::vector<glm::vec3>> k)
{
	for (int ui = 0; ui < uiMax; ui++)
	{
		for (int vi = 0; vi < viMax; vi++)
		{
			float u0 = (float)ui / (float)uiMax;
			float v0 = (float)vi / (float)viMax;
			float u1 = (float)(ui + 1) / (float)uiMax;
			float v1 = (float)(vi + 1) / (float)viMax;

			glm::vec3 a = bezierSurface(u0, v0, k);
			glm::vec2 uvA = glm::vec2(u0, v0);
			glm::vec3 b = bezierSurface(u1, v0, k);
			glm::vec2 uvB = glm::vec2(u1, v0);
			glm::vec3 c = bezierSurface(u0, v1, k);
			glm::vec2 uvC = glm::vec2(u0, v1);
			glm::vec3 d = bezierSurface(u1, v1, k);
			glm::vec2 uvD = glm::vec2(u1, v1);

			addQuad(a, uvA, b, uvB, c, uvC, d, uvD);
		}
	}
}

void ProceduralShapes::makeBezierSurfaceCaller()
{
	std::vector<std::vector<glm::vec3>> k = 
	{
		{ glm::vec3(-1, 0, -1), glm::vec3(-0.3f, 0.25f, -1), glm::vec3(0.3f, 0.25f, -1), glm::vec3(1, 0, -1) },
		{ glm::vec3(-1, 0.25f, -0.3f), glm::vec3(-0.3f, 0.5f, -0.3f), glm::vec3(0.3f, 0.5f, -0.3f), glm::vec3(1, 0.25f, -0.3f) },
		{ glm::vec3(-1, 0.25f, 0.3f), glm::vec3(-0.3f, 0.5f, 0.3f), glm::vec3(0.3f, 0.5f, 0.3f), glm::vec3(1, 0.25f, 0.3f) },
		{ glm::vec3(-1, 0, 1), glm::vec3(-0.3f, 0.25f, 1), glm::vec3(0.3f, 0.25f, 1), glm::vec3(1, 0, 1) }
	};
	makeBezierSurface(16, 16, k);
}

glm::vec3 ProceduralShapes::bezierSurface(float u, float v, std::vector<std::vector<glm::vec3>> k)
{
	glm::vec3 p = glm::vec3();

	// Iterate over the control points kij
	int n = k.size() - 1;
	int m = k[0].size() - 1;
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <=m; j++)
		{
			float inu = bernsteinPolynomial(i, n, u);
			float jmv = bernsteinPolynomial(j, m, v);
			p += k[i][j] * bernsteinPolynomial(i, n, u) * bernsteinPolynomial(j, m, v);
		}
	}

	return p;
}

float ProceduralShapes::bernsteinPolynomial(int i, int n, float u)
{
	return binomialCoefficient(n, i) * powf(u, (float)i) * powf(1.0f - u, (float)(n - i));
}

float ProceduralShapes::binomialCoefficient(int n, int k)
{
	float result = 1.0f;
	for (int i = 1; i <= k; i++)
	{
		result *= n + 1 - i;
		result /= i;
	}
	return result;
}

glm::vec3 ProceduralShapes::sphereV(float r, float theta, float phi)
{
	// x = r cos(theta)sin(phi)
	// y = r sin(theta)sin(phi)
	// z = r cos(phi)
	return glm::vec3(r * cosf(theta) * sinf(phi), r * sinf(theta) * sinf(phi), r * cosf(phi));
}

ProceduralShapes::ProceduralShapes(primitive type)
{
	switch (type)
	{
	case ProceduralShapes::cube:
		makeCube();
		break;
	case ProceduralShapes::sphere:
		makeSphere(16, 16);
		break;
	case ProceduralShapes::cylinder:
		makeCylinder(16);
		break;
	case ProceduralShapes::bezier:
		makeBezierSurfaceCaller(); // switch won't let me declare stuff inside the switch.
		break;
	default:
		break;
	}
}

ProceduralShapes::~ProceduralShapes()
{
}

std::vector<GLfloat> ProceduralShapes::getVertices()
{
	return vertices;
}

std::vector<GLushort> ProceduralShapes::getElements()
{
	return elements;
}
