#pragma once
#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <Tema1\SpaceObject.h>
#include <Tema1\Player.h>
#include <Tema1\Transform2D.h>


Player::Player()
{
	this->lifes = 3;
	this->gameStatus = true;
	this->playerShip = new SpaceObject();
	this->lifeModelMatrix = glm::mat3(1);
}

Player::~Player()
{
}

Mesh* Player::createLife(std::string name, glm::vec3 lifeCenter)
{
	int lifeSide = 20;
	glm::vec3 color = glm::vec3(1,0,0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(lifeCenter + glm::vec3(-lifeSide / 6, -lifeSide, 0), color),
		VertexFormat(lifeCenter + glm::vec3(lifeSide / 6, -lifeSide, 0), color),
		VertexFormat(lifeCenter + glm::vec3(lifeSide / 6, lifeSide, 0), color),
		VertexFormat(lifeCenter + glm::vec3(-lifeSide / 6,  lifeSide, 0), color),

	};

	Mesh* life = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	indices.push_back(0);
	indices.push_back(2);

	life->InitFromData(vertices, indices);
	return life;

}

int Player::getLifes()
{
	return lifes;
}

bool Player::getGameStatus()
{
	return gameStatus;
}

std::vector<Mesh*> Player::getLifeList()
{
	return lifeList;
}

SpaceObject* Player::getShip()
{
	return playerShip;
}

glm::mat3 Player::getlifeModelMatrix()
{
	return lifeModelMatrix;
}

void Player::setLifeList(Mesh* mesh)
{
	this->lifeList.push_back(mesh);
}

void Player::removeLife() {
	this->lifeList.pop_back();
}

void Player::setShip(SpaceObject* playerShip)
{
	this->playerShip = playerShip;
}

void Player::setGameStatus(bool status)
{
	this->gameStatus = status;
}

void Player::setLifes(int lifes)
{
	this->lifes = lifes;
}
