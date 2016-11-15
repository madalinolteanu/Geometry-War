#pragma once
#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include <Tema1\Transform2D.h>
#include <Tema1\SpaceObject.h>
#include <Tema1\Player.h>
#include <Tema1\Food.h>

class Space : public SimpleScene
{
	public:
		Space();
		~Space();

		void Init() override;

	private:

		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		void DrowMoves();
		void redScreen(float deltaTimeSeconds);
		void drowEnemy();
		void drowLifes();
		void drowBullet();
		void renderEnemy();
		void renderBullet();
		void renderMyShip();
		void renderLifes();
		void drowFood();
		void renderFood();
		bool killShip(SpaceObject* enemyShip, SpaceObject *glont);
		bool hitEnemy(SpaceObject* enemyShip, SpaceObject *myShip);
		bool eatFood(SpaceObject * food, SpaceObject * myShip);
		SpaceObject* Space::returnRadian(SpaceObject* myShip, SpaceObject* enemyShip);

		Player *player;
		glm::vec3 myColor = glm::vec3(0, 0, 1);
		glm::vec3 enemyColor = glm::vec3(1, 0, 0);
		std::string myType = "myShip";
		std::string myName = "myShip";
		std::string enemyType = "enemyShip";
		std::string enemyName = "enemyShip";
		std::vector<SpaceObject*> spaceShipList;
		SpaceObject* myShip;
		clock_t c_start;
		clock_t c_eat;

		bool toggleButton = false;
		bool translateBullet = false;
		int countBullet = 0;
		int countEnemy = 0;
		double randX;
		double randY;
		double angle;
		int radius;
		float translateX = 5;
		float translateY = 5;
		float trBulletY;
		float trBulletX;
		float angularStep;
		float redColor =  0.0f;
		float delayTime = 2000.0f;
		int totalEnemy = 0;
		float deltaTime;
		int SpaceX;
		int SpaceY;
		SpaceObject* food;
		std::string type1 = "speedFood";
		std::string type2 = "imunityFood";
		std::string type3 = "lifeFood";
};
