#pragma once

#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <Tema1\SpaceObject.h>
#include <Tema1\Bullet.h>
using namespace std;

class SpaceShip : public SpaceObject
{
	public:
		SpaceShip();
		SpaceShip(glm::vec3 center);
		SpaceShip(glm::vec3 center, string name);
		~SpaceShip();

	private:
		string myType = "myShip";
		string myName = "myShip";
		string enemyType = "enemyShip";
		glm::vec3 myShipColor = glm::vec3(0.5f, 0, 0.5f);
		glm::vec3 enemyColor = glm::vec3(0, 0, 1);
		int shipSide = 50;
		int myShipSpeed = 4;
		vector<SpaceObject*> bulletList;
};