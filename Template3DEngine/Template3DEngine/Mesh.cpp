#include "Mesh.h"


// Default ctor is for a tetrahedron!
Mesh::Mesh()
{
	std::vector<glm::vec3> positions = {
		glm::vec3(1, 1, 0),
		glm::vec3(-1, 1, 0),
		glm::vec3(0, -1, 0),
		glm::vec3(0, 0, -1) };
	std::vector<glm::vec2> uvs = {
		glm::vec2(0, 0),
		glm::vec2(0, 1),
		glm::vec2(1, 0),
		glm::vec2(1, 1) };
	std::vector<glm::vec3> normals = {
		glm::vec3(1, 1, 0),
		glm::vec3(-1, 1, 0),
		glm::vec3(1, -1, 0),
		glm::vec3(0, 0, -1) };
	std::vector<unsigned short> elements = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 1,
		3, 2, 1 };

	std::vector<GLfloat> vertices;
	for (int i = 0; i < 4; ++i)
	{
		vertices.push_back(positions[i].x);
		vertices.push_back(positions[i].y);
		vertices.push_back(positions[i].z);
		vertices.push_back(uvs[i].x);
		vertices.push_back(uvs[i].y);
		vertices.push_back(normals[i].x);
		vertices.push_back(normals[i].y);
		vertices.push_back(normals[i].z);
	}

	initBuffers(vertices, elements);
}

void Mesh::initBuffers(const std::vector<GLfloat>& vertices, const std::vector<GLushort>& elements)
{
	// Generate buffers.
	glGenVertexArrays(1, &vaoIndex);
	glGenBuffers(1, &vboIndex);
	
	// Bind buffers.
	glBindVertexArray(vaoIndex);
	glBindBuffer(GL_ARRAY_BUFFER, vboIndex);

	this->numElements = elements.size();

	// Upload Data
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Direct variable in vertex shader where its data resides on the buffer.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof( GL_FLOAT ) * 8, (void*)(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof( GL_FLOAT ) * 8, (void*)(sizeof(GL_FLOAT) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof( GL_FLOAT ) * 8, (void*)(sizeof(GL_FLOAT) * 5));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//Upload element data
	GLuint eboIndex;
	glGenBuffers(1, &eboIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * elements.size(), &elements[0], GL_STATIC_DRAW);
}

void Mesh::loadTexture(std::string textureFilePath)
{
	if (textureFilePath != "")
	{
		textureID = SOIL_load_OGL_texture(
			textureFilePath.c_str(), SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y
			);

	}
}

Mesh::Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLushort>& elements, std::string textureFilePath)
{
	initBuffers(vertices, elements);
	loadTexture(textureFilePath);
}

Mesh::Mesh(std::string fileName, std::string textureFilePath)
{
	std::vector<glm::vec3> positions; // Hold data from 'v'
	std::vector<glm::vec2> uvs; // Hold data from 'vt'
	std::vector<glm::vec3> normals; // Hold data from 'vn'
	std::vector<GLfloat> vertices; // Acted upon by each 'f' position/texture[/normal] set
	std::vector<GLushort> elements; // Holds indices for each TRIANGLE, NOT QUAD.  DO NOT PUSH QUADS.
	std::unordered_map<std::string, GLushort> elementDataMap; // Faster way to ensure we don't include a vertex more than once
	GLushort elementIndexCounter = 0;

	std::ifstream inStream(fileName, std::ios::in);
	if (!inStream.is_open())
	{
		return;
	}
	
	std::string line;
	std::string substring;
	bool readNormals = false; // Assume until proven otherwise that there are no normals to read

	while (std::getline(inStream, line))
	{
		std::istringstream sstream(line);
		sstream >> substring;
		if (substring == "v")
		{
			float x, y, z;
			sstream >> x >> y >> z;
			positions.push_back(glm::vec3(x, y, z));
		}
		else if (substring == "vt")
		{
			float u, v;
			sstream >> u >> v;
			uvs.push_back(glm::vec2(u, v));
		}
		else if (substring == "vn")
		{
			readNormals = true;
			float x, y, z;
			sstream >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		else if (substring == "f")
		{
			unsigned short Apos, Auv, Anorm, Bpos, Buv, Bnorm, Cpos, Cuv, Cnorm, Dpos = 0, Duv, Dnorm;
			char devnull;
			sstream >> Apos >> devnull >> Auv;
			if (readNormals) sstream >> devnull >> Anorm;
			sstream >> Bpos >> devnull >> Buv;
			if (readNormals) sstream >> devnull >> Bnorm;
			sstream >> Cpos >> devnull >> Cuv;
			if (readNormals) sstream >> devnull >> Cnorm;
			bool isQuad = false;
			if (sstream >> Dpos)
			{
				isQuad = true;
				sstream >> devnull >> Duv;
				if (readNormals) sstream >> devnull >> Dnorm;
			}
			Apos -= 1; Auv -= 1;
			Bpos -= 1; Buv -= 1;
			Cpos -= 1; Cuv -= 1;
			if (readNormals)
			{
				Anorm -= 1;
				Bnorm -= 1;
				Cnorm -= 1;
			}
			if (isQuad) { Dpos -= 1; Duv -= 1; if (readNormals) { Dnorm -= 1; } }

			#pragma region PUSHA
			std::string AElementData = std::to_string(Apos) + '/' + std::to_string(Auv) + '/' + ((readNormals)?(std::to_string(Anorm)):(" "));
			if (elementDataMap.find(AElementData) == elementDataMap.end())
			{
				vertices.push_back(positions[Apos].x);
				vertices.push_back(positions[Apos].y);
				vertices.push_back(positions[Apos].z);
				vertices.push_back(uvs[Auv].x);
				vertices.push_back(uvs[Auv].y);
				if (readNormals)
				{
					vertices.push_back(normals[Anorm].x);
					vertices.push_back(normals[Anorm].y);
					vertices.push_back(normals[Anorm].z);
				}
				else
				{
					glm::vec3 normal = glm::normalize(glm::cross(positions[Cpos] - positions[Apos], positions[Bpos] - positions[Apos]));
					vertices.push_back(normal.x);
					vertices.push_back(normal.y);
					vertices.push_back(normal.z);
				}

				elementDataMap.insert(std::make_pair(AElementData, elementIndexCounter));
				elementIndexCounter++;
			}
			elements.push_back(elementDataMap[AElementData]);
			#pragma endregion

			#pragma region PUSHB
			std::string BElementData = std::to_string(Bpos) + '/' + std::to_string(Buv) + '/' + ((readNormals) ? (std::to_string(Bnorm)) : (" "));
			if (elementDataMap.find(BElementData) == elementDataMap.end())
			{
				vertices.push_back(positions[Bpos].x);
				vertices.push_back(positions[Bpos].y);
				vertices.push_back(positions[Bpos].z);
				vertices.push_back(uvs[Buv].y);
				vertices.push_back(uvs[Buv].x);
				if (readNormals)
				{
					vertices.push_back(normals[Bnorm].x);
					vertices.push_back(normals[Bnorm].y);
					vertices.push_back(normals[Bnorm].z);
				}
				else
				{
					glm::vec3 normal = glm::normalize(glm::cross(positions[Apos] - positions[Bpos], positions[Dpos] - positions[Bpos]));
					vertices.push_back(normal.x);
					vertices.push_back(normal.y);
					vertices.push_back(normal.z);
				}

				elementDataMap.insert(std::make_pair(BElementData, elementIndexCounter));
				elementIndexCounter++;
			}
			elements.push_back(elementDataMap[BElementData]);
			#pragma endregion
			
			#pragma region PUSHC
			std::string CElementData = std::to_string(Cpos) + '/' + std::to_string(Cuv) + '/' + ((readNormals) ? (std::to_string(Cnorm)) : (" "));
			if (elementDataMap.find(CElementData) == elementDataMap.end())
			{
				vertices.push_back(positions[Cpos].x);
				vertices.push_back(positions[Cpos].y);
				vertices.push_back(positions[Cpos].z);
				vertices.push_back(uvs[Cuv].y);
				vertices.push_back(uvs[Cuv].x);
				if (readNormals)
				{
					vertices.push_back(normals[Cnorm].x);
					vertices.push_back(normals[Cnorm].y);
					vertices.push_back(normals[Cnorm].z);
				}
				else
				{
					glm::vec3 normal = glm::normalize(glm::cross(positions[Dpos] - positions[Cpos], positions[Apos] - positions[Cpos]));
					vertices.push_back(normal.x);
					vertices.push_back(normal.y);
					vertices.push_back(normal.z);
				}

				elementDataMap.insert(std::make_pair(CElementData, elementIndexCounter));
				elementIndexCounter++;
			}
			elements.push_back(elementDataMap[CElementData]);
			#pragma endregion

			if (isQuad)
			{
				#pragma region PUSHD
				std::string DElementData = std::to_string(Dpos) + '/' + std::to_string(Duv) + '/' + ((readNormals) ? (std::to_string(Dnorm)) : (" "));
				if (elementDataMap.find(DElementData) == elementDataMap.end())
				{
					vertices.push_back(positions[Dpos].x);
					vertices.push_back(positions[Dpos].y);
					vertices.push_back(positions[Dpos].z);
					vertices.push_back(uvs[Duv].y);
					vertices.push_back(uvs[Duv].x);
					if (readNormals)
					{
						vertices.push_back(normals[Dnorm].x);
						vertices.push_back(normals[Dnorm].y);
						vertices.push_back(normals[Dnorm].z);
					}
					else
					{
						glm::vec3 normal = glm::normalize(glm::cross(positions[Bpos] - positions[Dpos], positions[Cpos] - positions[Dpos]));
						vertices.push_back(normal.x);
						vertices.push_back(normal.y);
						vertices.push_back(normal.z);
					}

					elementDataMap.insert(std::make_pair(DElementData, elementIndexCounter));
					elementIndexCounter++;
				}
				elements.push_back(elementDataMap[DElementData]);
				#pragma endregion
				
				#pragma region PUSHC
				elements.push_back(elementDataMap[CElementData]);
				#pragma endregion
				
				#pragma region PUSHB
				elements.push_back(elementDataMap[BElementData]);
				#pragma endregion
			}
		}
	}

	if (inStream.is_open())
	{
		inStream.close();
	}

	initBuffers(vertices, elements);
	loadTexture(textureFilePath);
}

Mesh::Mesh(ProceduralShapes::primitive type)
{
	ProceduralShapes shape = ProceduralShapes(type);
	initBuffers(shape.getVertices(), shape.getElements());
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vaoIndex);
	glDeleteBuffers(1, &vboIndex);
}

void Mesh::draw()
{
	if (textureID == 0)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glBindVertexArray(vaoIndex);
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_SHORT, (void *)0);
}
