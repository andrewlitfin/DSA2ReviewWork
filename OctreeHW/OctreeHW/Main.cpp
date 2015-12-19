#include "BinaryTree.h"
#include "QuadTree.h"
#include "OcTree.h"
#include <vector>
#include <random>
#include <iostream>
#include <string>
#include <glm\glm.hpp>

// For simplicity, I decided to all the colliders AABBs.

int main()
{
	std::vector<Collider3D> randoms;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> cGen(0, 16);
	std::uniform_real_distribution<> eGen(1, 2);

	for (int i = 0; i < 10; i++)
	{
		randoms.push_back(Collider3D(glm::vec3((float)cGen(gen), (float)cGen(gen), (float)cGen(gen)), glm::vec3((float)eGen(gen), (float)eGen(gen), (float)eGen(gen))));
	}

	OcTree* Tree = new OcTree(glm::vec3(8, 8, 8), glm::vec3(8, 8, 8));

	Tree->print();

	bool loop = true;
	std::cout << "Commands are add, check, print, and exit." << std::endl;
	int currentRandom = 0;
	
	while (loop)
	{
		std::string ui;
		std::cout << "Input command > ";
		std::getline(std::cin, ui);
		if (ui == "add")
		{
			if (currentRandom < 10)
			{
				std::cout << "Adding random collider number " << currentRandom << std::endl;
				Tree->add(&(randoms[currentRandom]));
				currentRandom++;
			}
			else
			{
				std::cout << "No more colliders to add!" << std::endl;
			}
		}
		else if (ui == "addn")
		{
			std::cout << "How many? > ";
			int in;
			std::cin >> in;
			for (int i = 0; i < in; i++)
			{
				Tree->add(new Collider3D(glm::vec3((float)cGen(gen), (float)cGen(gen), (float)cGen(gen)), glm::vec3((float)eGen(gen), (float)eGen(gen), (float)eGen(gen))));
			}
			std::cin.ignore();
		}
		else if (ui == "check")
		{
			std::cout << "Checking collision." << std::endl;
			Collider3D hai(glm::vec3((float)cGen(gen), (float)cGen(gen), (float)cGen(gen)), glm::vec3((float)eGen(gen), (float)eGen(gen), (float)eGen(gen)));
			hai.print();
			if (Tree->collidesWith(&hai))
			{
				std::cout << "Collides with Tree." << std::endl;
			}
			else
			{
				std::cout << "Does not collide with Tree." << std::endl;
			}
		}
		else if (ui == "print")
		{
			Tree->print();
		}
		else if (ui == "exit")
		{
			loop = false;
		}
		else if (ui == "117")
		{
			std::cout << "If you haven't mastered even these primitives, then Man has not attained the Mantle." << std::endl;
		}
	}

	std::cout << "End of line." << std::endl;
	std::cin.get();
	return 0;
}