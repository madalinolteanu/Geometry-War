#pragma once
#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class SpaceObject 
{
	public:
		SpaceObject();
		~SpaceObject();

		//Getters//
		 float getX();
		 float getY();
		 glm::vec3 getCenter();
		 double getRadian();
		 int getSide();
		 std::string getName();
		 std::string getType();
		 glm::vec3 getColor();
		 glm::mat3 getModelMatrix();
		 glm::vec3 getInitialCenter();
		 Mesh* getMesh();
		 std::vector<SpaceObject*> getBulletList();
		 bool getBadEnemy();
		 float getSpeed();
		 bool getPower();
		 std::string getPowerType();


		//Setters//
		 void setX(float spaceX);
		 void setY(float spaceY);
		 void setCenter(glm::vec3 center);
		 void setRadian(double grade);
		 void setSide(int shipSide);
		 void setName(std::string name);
		 void setType(std::string type);
		 void setColor(glm::vec3 color);
		 void setModelMatrix(glm::mat3 modelMatrix);
		 void setMesh(Mesh* shipMesh);
		 void setBadEnemy(bool badEnemy);
		 void setSpeed(float speed);
		 void setInitialCenter(glm::vec3 center);
		 void setPower(bool power);
		 void setPowerType(std::string powerType);

		 Mesh* CreateShip(std::string shipName, glm::vec3 shipCenter, int shipLength, glm::vec3  shipColor);
		 Mesh* CreateBullet(std::string name, glm::vec3 bulletCenter, int bulletLength, glm::vec3 color);
		 Mesh* CreateFood(std::string name, glm::vec3 bulletCenter, int bulletLength, glm::vec3 color);

		 void addBullet(SpaceObject* bullet);
		 void setBulletList(std::vector<SpaceObject*> bulletList);

	protected:
		float x;
		float y;
		glm::vec3 initialCenter;
		glm::vec3 center;
		double grade;
		int side;
		std::string name;
		std::string type;
		glm::vec3 color;
		glm::mat3 modelMatrix;
		Mesh* mesh;
		std::vector<SpaceObject*> bulletList;
		bool badEnemy;
		float speed;
		bool power;
		std::string powerType;
};