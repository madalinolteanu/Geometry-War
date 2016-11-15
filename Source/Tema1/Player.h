#pragma once
#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <Tema1\SpaceObject.h>

class Player
{
	public:
		Player();
		~Player();

		void setGameStatus(bool status);
		void setLifes(int lifes);
		void setLifeList(Mesh* mesh);
		void setShip(SpaceObject* playerShip);
		void removeLife();



		int getLifes();
		bool getGameStatus();
		std::vector<Mesh*> getLifeList();
		SpaceObject* getShip();
		glm::mat3 getlifeModelMatrix();
		

		Mesh* createLife(std::string name, glm::vec3 bulletCenter);

	
	private:
		SpaceObject *playerShip;
		int lifes;
		bool gameStatus;
		std::vector<Mesh*> lifeList;
		glm::mat3 lifeModelMatrix;



};