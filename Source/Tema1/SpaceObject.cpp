#include <iostream>
#include <Core/Engine.h>
#include <Tema1\SpaceObject.h>

SpaceObject::SpaceObject()
{
	glm::mat3 modelMatrix = glm::mat3(1);
	x = 0;
	y = 0;
	glm::vec3 center;
	side = 0;
	grade = 0.f;
	color = glm::vec3(0,0,0);
	name = "";
	std::vector<SpaceObject> bulletList;
	badEnemy = false;
}

SpaceObject::~SpaceObject()
{
}

void SpaceObject::setX(float x)
{
	this->x = x;
}

void SpaceObject::setY(float y)
{
	this->y = y;
}

void SpaceObject::setCenter(glm::vec3 center)
{
	this->center = center;
}

void SpaceObject::setRadian(double grade)
{
	this->grade = grade;
}

void SpaceObject::setSide(int side)
{
	this->side = side;
}

void SpaceObject::setName(std::string name)
{
	this->name = name;
}

void SpaceObject::setType(std::string type)
{
	this->type = type;
}

void SpaceObject::setColor(glm::vec3 color)
{
	this->color = color;
}

void SpaceObject::setModelMatrix(glm::mat3 modelMatrix)
{
	this->modelMatrix = modelMatrix;
}

void SpaceObject::setMesh(Mesh * mesh)
{
	this->mesh = mesh;
}

void SpaceObject::setBadEnemy(bool badEnemy)
{
	this->badEnemy = badEnemy;
}

void SpaceObject::setInitialCenter(glm::vec3 initialCenter) {
	this->initialCenter = initialCenter;
}

void SpaceObject::setPower(bool power)
{
	this->power = power;
}

void SpaceObject::setPowerType(std::string powerType)
{
	this->powerType = powerType;
}

void SpaceObject::setSpeed(float speed)
{
	this->speed = speed;
}

bool SpaceObject::getBadEnemy()
{
	return badEnemy;
}

float SpaceObject::getSpeed()
{
	return speed;
}

bool SpaceObject::getPower()
{
	return power;
}

std::string SpaceObject::getPowerType()
{
	return powerType;
}

float SpaceObject::getX() {
	return x;
}

float SpaceObject::getY()
{
	return y;
}

glm::vec3 SpaceObject::getCenter()
{
	return center;
}

double SpaceObject::getRadian()
{
	return grade;
}

int SpaceObject::getSide()
{
	return side;
}

std::string SpaceObject::getName()
{
	return name;
}

std::string SpaceObject::getType()
{
	return type;
}

glm::vec3 SpaceObject::getColor()
{
	return color;
}

glm::mat3 SpaceObject::getModelMatrix()
{
	return modelMatrix;
}

glm::vec3 SpaceObject::getInitialCenter()
{
	return initialCenter;
}

Mesh * SpaceObject::getMesh()
{
	return mesh;
}