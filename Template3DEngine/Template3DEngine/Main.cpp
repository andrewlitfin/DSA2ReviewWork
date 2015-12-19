#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glew.h>
#include <glfw3.h>
#include <SOIL.h>
#include <vector>
using namespace std;
using namespace glm;

#include "ShaderManager.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Camera.h"

//#define PADDLEGAME
#define PROCEDURALMODELS

// MAKE GLOBAL ARRAY?
bool Wpressed = false;
bool Spressed = false;
bool Ipressed = false;
bool Kpressed = false;
// </make>

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == GLFW_KEY_W)
	{
		if (action == GLFW_PRESS)
		{
			Wpressed = true;
		}
		else
		{
			Wpressed = false;
		}
	}
	else if (key == GLFW_KEY_S)
	{
		if (action == GLFW_PRESS)
		{
			Spressed = true;
		}
		else
		{
			Spressed = false;
		}
	}
	else if (key == GLFW_KEY_I)
	{
		if (action == GLFW_PRESS)
		{
			Ipressed = true;
		}
		else
		{
			Ipressed = false;
		}
	}
	else if (key == GLFW_KEY_K)
	{
		if (action == GLFW_PRESS)
		{
			Kpressed = true;
		}
		else
		{
			Kpressed = false;
		}
	}
}

int main()
{
	// Initialize the window library,
	// create a windowed mode window and its OpenGL context,
	// and make that context the currently active one
	if (!glfwInit()) return false;
	GLFWwindow* windowPtr = glfwCreateWindow(800, 600, "Template 3D Engine", NULL, NULL);
	if (!windowPtr)
	{
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(windowPtr);

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	// Set up any other necessary variables / engage drawing modes.
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	// Load Shader.
	GLuint shaderProgramIndex = ShaderManager::loadShaderProgram("Shaders/vShader.glsl", "Shaders/fShader.glsl");
	if (shaderProgramIndex == 0)
	{
		cout << "Shaders failed to load." << endl;
		return false;
	}
	glUseProgram(shaderProgramIndex);

	// Start adding other functionality here, like more meshes,
	// assigning user interface callbacks,
	// camera with view-screen matrix (view, projection),
	// lights, textures, game physics with game objects
	// and model-world matrix (translation, rotation, scaling),
	// putting Game Objects, Meshes & textures into collections.
	glfwSetKeyCallback(windowPtr, keyCallback);
	Camera* camera = new Camera(shaderProgramIndex);
	camera->setLocation(glm::vec3(0, 0, 5));

	glm::vec3 light = glm::vec3(0, 1, 0);
	glUniform3fv(glGetUniformLocation(shaderProgramIndex, "light"), 1, &light[0]);

	// MOVE ALL THIS TO GAME CLASS?
	std::vector<GameObject*> gos;
#ifdef PROCEDURALMODELS
	Mesh* cube = new Mesh(ProceduralShapes::primitive::cube);
	Mesh* cylinder = new Mesh(ProceduralShapes::primitive::cylinder);
	Mesh* sphere = new Mesh(ProceduralShapes::primitive::sphere);
	Mesh* bezier = new Mesh(ProceduralShapes::primitive::bezier);
	gos.push_back(new GameObject(cube, shaderProgramIndex));
	gos.push_back(new GameObject(cylinder, shaderProgramIndex));
	gos.push_back(new GameObject(sphere, shaderProgramIndex));
	gos.push_back(new GameObject(bezier, shaderProgramIndex));
	gos[0]->setLocation(glm::vec3(-3, 0, 0));
	gos[1]->setLocation(glm::vec3(-1, 0, 0));
	gos[2]->setLocation(glm::vec3(1, 0, 0));
	gos[3]->setLocation(glm::vec3(3, 0, 0));
	for (int i = 0; i < 4; i++) gos[i]->setAngularVelocity(glm::two_pi<float>() * 0.2f);
#elif PADDLEGAME
	Mesh* box = new Mesh("box.obj", "TestTexture.png");
	gos.push_back(new GameObject(box, shaderProgramIndex)); // PADDLE 0 (player 1)
	gos.push_back(new GameObject(box, shaderProgramIndex)); // PADDLE 1 (player 2)
	gos.push_back(new GameObject(box, shaderProgramIndex)); // BALL
	gos[0]->setLocation(glm::vec3(-1, 0, 0));
	gos[1]->setLocation(glm::vec3(1, 0, 0));
	gos[0]->setScale(glm::vec3(0.125f, 1.0f, 1.0f));
	gos[1]->setScale(glm::vec3(0.125f, 1.0f, 1.0f));
	gos[2]->setLocation(glm::vec3(0, 0, 0));
	gos[2]->setScale(glm::vec3(0.1f, 0.1f, 0.1f));
	gos[2]->setVelocity(glm::vec3(-0.5f, 0.15f, 0.0f));
#endif
	// </move>

	float activeTime = (float)glfwGetTime();

	// Game loop
	while (!glfwWindowShouldClose(windowPtr))
	{
		float dt = (float)glfwGetTime() - activeTime;
		activeTime += dt;

		// Process queued window and input callback events.
		glfwPollEvents();

#ifdef PADDLEGAMELOGIC
		// LOGIC FOR PADDLE GAME (move to Game class?)
		// Move paddles
		glm::vec3 paddleSpeed = glm::vec3(0, 3, 0);
		if (Wpressed)
		{
			gos[0]->setVelocity(paddleSpeed);
		}
		else if (Spressed)
		{
			gos[0]->setVelocity(-paddleSpeed);
		}
		else
		{
			gos[0]->setVelocity(glm::vec3());
		}
		if (Ipressed)
		{
			gos[1]->setVelocity(paddleSpeed);
		}
		else if (Kpressed)
		{
			gos[1]->setVelocity(-paddleSpeed);
		}
		else
		{
			gos[1]->setVelocity(glm::vec3());
		}
		// Collision detection
		float xSumHalfwidths = 0.0625f + 0.05f; // Sum of paddle halfwidth and pong halfwidth
		float ySumHalfwidths = 0.5f + 0.05f;

		// Check ball against paddle 1
		glm::vec3 c1 = gos[0]->getLocation() - gos[2]->getLocation();
		if (!(fabsf(c1.x) > xSumHalfwidths || fabsf(c1.y) > ySumHalfwidths))
		{
			glm::vec3 newvelocity = gos[2]->getVelocity();
			newvelocity.x *= -1;
			gos[2]->setVelocity(newvelocity);
		}
		// Check ball against paddle 2
		glm::vec3 c2 = gos[1]->getLocation() - gos[2]->getLocation();
		if (!(fabsf(c2.x) > xSumHalfwidths || fabsf(c2.y) > ySumHalfwidths))
		{
			glm::vec3 newvelocity = gos[2]->getVelocity();
			newvelocity.x *= -1;
			gos[2]->setVelocity(newvelocity);
		}
		// </logic>
#endif

		// Update
		// Update Camera and Game Objects locations here.
		camera->update(dt);
		for each (GameObject* go in gos)
		{
			go->update(dt);
		}

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Call the draw methods of other meshes.
		camera->draw();
		for each (GameObject* go in gos)
		{
			go->draw();
		}

		// Swap the front (what the screen displays)
		// and back (what OpenGL draws to) buffers.
		glfwSwapBuffers(windowPtr);
	}

	for each (GameObject* go in gos)
	{
		delete go;
	}

	return 0;
}