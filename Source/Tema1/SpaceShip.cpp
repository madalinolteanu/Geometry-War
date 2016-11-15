#include <iostream>
#include <Core/Engine.h>
#include <Tema1\SpaceShip.h>
#include <Tema1\Bullet.h>

using namespace std;

SpaceShip::SpaceShip()
{
}

SpaceShip::~SpaceShip()
{
}

SpaceShip::SpaceShip(glm::vec3 center)
{
	this->setColor(myShipColor);
	this->setType(myType);
	this->setName(myName);
	this->setSide(shipSide);
	this->setCenter(center);
	this->setSpeed(myShipSpeed);
	
}

SpaceShip::SpaceShip(glm::vec3 center, string name) {
	
	this->setName(name);
	this->setType(enemyType);
	this->setColor(enemyColor);
	this->setSide(shipSide);
	this->setCenter(center);
	this->setSpeed(0.8f);
	this->setInitialCenter(center);
}

std::vector<SpaceObject*> SpaceObject::getBulletList()
{
	return bulletList;
}

void SpaceObject::addBullet(SpaceObject * bullet) {
	this->bulletList.push_back(bullet);
}


void SpaceObject::setBulletList(std::vector<SpaceObject*> bulletList) {

	this->bulletList = bulletList;
}

Mesh* SpaceObject::CreateShip(std::string name, glm::vec3 center, int length, glm::vec3 color)
{

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center, color),
		VertexFormat(center + glm::vec3(length / 2, length / 2, 0), color),
		VertexFormat(center + glm::vec3(length / 2,  -length / 2, 0), color),
		VertexFormat(center - glm::vec3(length / 2, length / 2, 0), color),
		VertexFormat(center - glm::vec3(length / 2, -length / 2, 0), color),
	};

	Mesh* spaceShip = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4 };

	indices.push_back(0);
	indices.push_back(2);

	spaceShip->InitFromData(vertices, indices);
	return spaceShip;
}