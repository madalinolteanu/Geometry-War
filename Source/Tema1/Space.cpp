#include <vector>
#include <iostream>
#include <chrono>
#include <Core/Engine.h>
#include <Tema1\Space.h>
#include <Tema1\SpaceShip.h>
#include <Tema1\Bullet.h>
#include <Tema1\Player.h>

using namespace std;

Space::Space()
{
}

Space::~Space()
{
	
}

void Space::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	SpaceX = resolution.x;
	SpaceY = resolution.y;
	camera->SetOrthographic(0, (float)SpaceX, 0, (float)SpaceY, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	cameraInput->SetActive(false);

	angularStep = 0;

	Player *player = new Player();
	this->player = player;

	glm::vec3 myCenter = glm::vec3((float)SpaceX / 2, (float)SpaceY / 2, 0);
	SpaceObject *myShip = new SpaceShip(myCenter);

	myShip->setInitialCenter(myCenter);
	myShip->setMesh(myShip->CreateShip(myShip->getName(), myShip->getInitialCenter(), myShip->getSide(), myShip->getColor()));
	AddMeshToList(myShip->getMesh());
	this->myShip = myShip;

	drowLifes();
	drowFood();
	c_start = clock();
}

void Space::FrameStart()
{

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	glViewport(0, 0, SpaceX, SpaceY);
}



void Space::Update(float deltaTimeSeconds)
{	
	if (player->getGameStatus()) {
		DrowMoves();
		renderLifes();
		
	}
	else {
		redScreen(deltaTimeSeconds);
	}
	
}

void Space::FrameEnd()
{

}

void Space::OnInputUpdate(float deltaTime, int mods)
{	
	glm::ivec2 resolution = window->GetResolution();
	if (!player->getGameStatus()) {
		myShip->setSpeed(0);
	}
	int speed = myShip->getSpeed();

	if (window->KeyHold(GLFW_KEY_W)) {
		if (myShip->getY() < (SpaceY / 2 - myShip->getSide())) {
			myShip->setY(myShip->getY() + speed);
			glm::vec3 center(myShip->getCenter().x, myShip->getCenter().y + speed, 0);
			myShip->setCenter(center);
		}

	}

	if (window->KeyHold(GLFW_KEY_S)) {
		if (myShip->getY() > ( -SpaceY / 2 + myShip->getSide())) {
			myShip->setY(myShip->getY() - speed);
			glm::vec3 center(myShip->getCenter().x, myShip->getCenter().y - speed, 0);
			myShip->setCenter(center);
		}
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		if (myShip->getX()  > ( -SpaceX / 2 + myShip->getSide())) {
			myShip->setX(myShip->getX() - speed);
			glm::vec3 center(myShip->getCenter().x - speed, myShip->getCenter().y, 0);
			myShip->setCenter(center);
		}
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		if (myShip->getX() < (SpaceX / 2 - myShip->getSide())) {
			myShip->setX(myShip->getX() + speed);
			glm::vec3 center(myShip->getCenter().x + speed, myShip->getCenter().y, 0);
			myShip->setCenter(center);
		}
	}
}

void Space::OnKeyPress(int key, int mods)
{

}

void Space::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Space::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (player->getGameStatus()) {
		glm::ivec2 resolution = window->GetResolution();
		myShip->setRadian((std::atan2(-mouseX + myShip->getCenter().x, SpaceY - mouseY - myShip->getCenter().y)));
	}
}

void Space::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (button == 1) {
		toggleButton = !toggleButton;
	}

	if (!player->getGameStatus()) {
		toggleButton = false;
	}
}

void Space::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Space::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Space::OnWindowResize(int width, int height)
{
}

bool Space::killShip(SpaceObject * enemyShip, SpaceObject * bullet)
{
	double x = INFINITE;
	double y = INFINITE;
	glm::ivec2 resolution = window->GetResolution();

	x = bullet->getCenter().x - sin(bullet->getRadian()) * bullet->getY();
	y = bullet->getCenter().y + cos(bullet->getRadian()) * bullet->getY();

	double enemy_x = enemyShip->getCenter().x;
	double enemy_y = enemyShip->getCenter().y;
	double distance = sqrt((enemy_x - x) * (enemy_x - x) + (enemy_y - y) * (enemy_y - y));
	
	if (distance < enemyShip->getSide() / 2 + bullet->getSide() / 2) {
		return true;
	}

	return false;
}

bool Space::hitEnemy(SpaceObject * enemyShip, SpaceObject * myShip)
{
	double enemy_x = enemyShip->getCenter().x;
	double enemy_y = enemyShip->getCenter().y;
	double myShip_x = myShip->getCenter().x;
	double myShip_y = myShip->getCenter().y;
	double distance = sqrt((enemy_x - myShip_x) * (enemy_x - myShip_x) + (enemy_y - myShip_y) * (enemy_y - myShip_y));

	if (distance < myShip->getSide() / 2 + enemyShip->getSide() / 2){
		return true;
	}
	return false;
}

bool Space::eatFood(SpaceObject * food, SpaceObject * myShip) {

	double x = INFINITE;
	double y = INFINITE;

	x = food->getCenter().x;
	y = food->getCenter().y;

	double myShip_x = myShip->getCenter().x;
	double myShip_y = myShip->getCenter().y;
	double distance = sqrt((myShip_x - x) * (myShip_x - x) + (myShip_y - y) * (myShip_y - y));

	if (distance < myShip->getSide() / 2 + food->getSide() / 2) {
		return true;
	}

	return false;
}

void Space::DrowMoves() {

	renderMyShip();

	float time = ((clock() - c_start) / (CLOCKS_PER_SEC / 1000));
	if (time > delayTime && player->getGameStatus()) {
		drowEnemy();
		c_start = clock();
	}

	if (toggleButton) {
		drowBullet();
	}

	renderEnemy();
	renderBullet();

	if (eatFood(myShip, food)) {
		myShip->setPower(true);
		myShip->setPowerType(food->getType());

		if (food->getType().compare(type1) == 0) {
			myShip->setSpeed(myShip->getSpeed() + 2);
			myShip->setMesh(myShip->CreateShip(myShip->getName(), myShip->getInitialCenter(), myShip->getSide(), glm::vec3(1, 0, 1)));
		}
		else if (myShip->getPowerType().compare(type2) == 0) {
			myShip->setMesh(myShip->CreateShip(myShip->getName(), myShip->getInitialCenter(), myShip->getSide(), glm::vec3(1, 1, 1)));

		} else if (food->getType().compare(type3) == 0) {
			player->setLifes(player->getLifes() + 1);
			glm::vec3 lifeCenter = glm::vec3(SpaceX - 20 * (player->getLifes()), SpaceY - 20, 0);
			player->setLifeList(player->createLife("life" + std::to_string((player->getLifes())), lifeCenter));
		}
		c_eat = clock() / CLOCKS_PER_SEC;
		this->food = new Food();
	}
	else if (!myShip->getPower()) {
		renderFood();
	}

	if (myShip->getPower() && (clock() / CLOCKS_PER_SEC) - c_eat == 5) {

		if (myShip->getPowerType().compare(type1) == 0) {
			myShip->setSpeed(myShip->getSpeed() - 2);
			myShip->setMesh(myShip->CreateShip(myShip->getName(), myShip->getInitialCenter(), myShip->getSide(), myShip->getColor()));
		} else if (myShip->getPowerType().compare(type2) == 0) {
			myShip->setMesh(myShip->CreateShip(myShip->getName(), myShip->getInitialCenter(), myShip->getSide(), myShip->getColor()));
		}

		myShip->setPowerType("");
		myShip->setPower(false);
		drowFood();
	}

	vector<SpaceObject*> bulletList = myShip->getBulletList();
	vector<SpaceObject*>::iterator iteratorShip = spaceShipList.begin();
	int i = 0;
	while (iteratorShip != spaceShipList.end()) {
		SpaceObject *enemyShip = spaceShipList[i];

		vector<SpaceObject*>::iterator iteratorBullet = bulletList.begin();
		int j = 0;
		while (iteratorBullet != bulletList.end()) {
			SpaceObject* bullet = bulletList[j];
			//Rotesc Bullet dupa Naveta//

			if (killShip(enemyShip, bullet)) {

				if (enemyShip->getBadEnemy()) {
					enemyShip->setSpeed(enemyShip->getSpeed() * 3);
					cout<< clock() / (CLOCKS_PER_SEC / 1000);
				}
				else {
					iteratorShip = spaceShipList.erase(iteratorShip);
					countEnemy--;
				}

				iteratorBullet = bulletList.erase(iteratorBullet);
				countBullet--;

			}

			double x = bullet->getCenter().x - sin(bullet->getRadian()) * bullet->getY();
			double y = bullet->getCenter().y + cos(bullet->getRadian()) * bullet->getY();
			if (y > SpaceY  && x > SpaceX || y < 0 && x < 0 || y < 0 && x > SpaceX || y > SpaceX && x < 0) {
				countBullet--;
				iteratorBullet = bulletList.erase(iteratorBullet);
			}

			if (countBullet > 0 && j < countBullet) {
				++j;
				++iteratorBullet;
			}
		}

		if (hitEnemy(enemyShip, myShip)) {
			if (myShip->getPowerType().compare(type2) != 0) {
				if (enemyShip->getBadEnemy()) {
					player->setLifes(player->getLifes() - 2);
					if (player->getLifes() != -1) {
						player->removeLife();
						player->removeLife();
					}
					else {
						player->removeLife();
					}
				}else {
					player->setLifes(player->getLifes() - 1);
					player->removeLife();
				}
			}	

			iteratorShip = spaceShipList.erase(iteratorShip);
			countEnemy--;
			if (player->getLifes() <= 0) {
				player->setGameStatus(false);
				translateY = 0;
			}
			if (countEnemy > 0 && i < countEnemy) {
				++i;
				++iteratorShip;
			}
		}
		else if (countEnemy > 0 && i < countEnemy) {
			++i;
			++iteratorShip;
		}
	}

	myShip->setBulletList(bulletList);
}

void Space::redScreen(float deltaTimeSeconds) {
	redColor += deltaTimeSeconds / 10;
	glClearColor(redColor, 0.0f, 0.0f, redColor);
	glClear(GL_COLOR_BUFFER_BIT);
	
}

void Space::drowEnemy() {

	glm::ivec2 resolution = window->GetResolution();
	radius = SpaceY / 2;
	countEnemy++;
	angle = (((double)rand() / (RAND_MAX)) + 1 )* M_PI * 2;
	randX = cos(angle)*radius + SpaceX / 2;
	randY = sin(angle)*radius + SpaceY / 2;
	
	//Create Enemy over the time//
	glm::vec3 enemyCenter = glm::vec3(randX, randY, 0);
	SpaceObject *enemyShip = new SpaceShip(enemyCenter, enemyName + to_string(countEnemy));

	if (rand() % 2 == 1) {
		enemyShip->setBadEnemy(true);
		enemyShip->setColor(glm::vec3(1, 1, 0));
	}
	enemyShip->setMesh(enemyShip->CreateShip(enemyShip->getName(), enemyShip->getInitialCenter(), enemyShip->getSide(), enemyShip->getColor()));
	spaceShipList.push_back(enemyShip);
	c_start = clock();
	totalEnemy++;

	if (totalEnemy % 3 == 0 && delayTime >= 550.0f) {
		delayTime -= 50.0f;
	}

}

void Space::drowBullet() {

		SpaceObject *bullet = new Bullet(myShip->getCenter());
		bullet->setRadian(myShip->getRadian());
		bullet->setName("bullet" + std::to_string(countBullet));
		bullet->setMesh(bullet->CreateBullet(bullet->getName(), bullet->getCenter(), bullet->getSide(), bullet->getColor()));
		myShip->addBullet(bullet);
		countBullet++;
		toggleButton = false;
}

void Space::drowLifes() {

	for (int i = 0; i < player->getLifes(); i++) {
		glm::vec3 lifeCenter = glm::vec3(SpaceX - 20 * (i + 1), SpaceY - 20, 0);
		player->setLifeList(player->createLife("life" + std::to_string(i), lifeCenter));
	}
}

void Space::renderLifes()
{
	vector<Mesh*> lifes = player->getLifeList();
	vector<Mesh*>::iterator iterator = lifes.begin();
	int i = 0;
	while (iterator != lifes.end()) {
		Mesh* mesh = lifes[i];
		RenderMesh2D(mesh, shaders["VertexColor"], player->getlifeModelMatrix());

		if (player->getLifes() > 0 && i < player->getLifes()) {
			++i;
			++iterator;
		}
	}
}

void Space::renderEnemy()
{
	Mesh* mesh;
	vector<SpaceObject*>::iterator iteratorShip = spaceShipList.begin();
	int i = 0;
	while (iteratorShip != spaceShipList.end()) {
		SpaceObject *enemyShip = spaceShipList[i];
		//Rotesc Inamic dupa Naveta//
		if (enemyShip->getSpeed() > 0.8f) {
			if (enemyShip->getBadEnemy()) {
				enemyShip->setSide(enemyShip->getSide() / 2);
				cout << clock() / (CLOCKS_PER_SEC / 1000);
			}
			enemyShip->setMesh(enemyShip->CreateShip(enemyShip->getName(), enemyShip->getInitialCenter(), enemyShip->getSide(), glm::vec3(1, 0, 0)));
			enemyShip->setBadEnemy(false);
		}
		
		enemyShip = returnRadian(myShip, enemyShip);
		enemyShip->setModelMatrix(Transform2D::Translate(enemyShip->getX(), enemyShip->getY()));
		enemyShip->setModelMatrix(enemyShip->getModelMatrix() * Transform2D::Translate(enemyShip->getCenter().x - enemyShip->getX(), enemyShip->getCenter().y - enemyShip->getY()));
		enemyShip->setModelMatrix(enemyShip->getModelMatrix() * Transform2D::Rotate(enemyShip->getRadian()));
		enemyShip->setModelMatrix(enemyShip->getModelMatrix() * Transform2D::Translate(-enemyShip->getCenter().x + enemyShip->getX(), -enemyShip->getCenter().y + enemyShip->getY()));


		RenderMesh2D(enemyShip->getMesh(), shaders["VertexColor"], enemyShip->getModelMatrix());

		if (countEnemy > 0 && i < countEnemy) {
			++i;
			++iteratorShip;
		}
	}
}

void Space::renderBullet()
{
	vector<SpaceObject*> bulletList = myShip->getBulletList();
	vector<SpaceObject*>::iterator iteratorBullet = bulletList.begin();
	int j = 0;
	while (iteratorBullet != bulletList.end()) {
		SpaceObject* bullet = bulletList[j];
		bullet->setY(bullet->getY() + translateY);
		bullet->setModelMatrix(Transform2D::Translate(bullet->getX(), bullet->getY()));
		bullet->setModelMatrix(bullet->getModelMatrix() * Transform2D::Translate(bullet->getCenter().x - bullet->getX(), bullet->getCenter().y - bullet->getY()));
		bullet->setModelMatrix(bullet->getModelMatrix() * Transform2D::Rotate(bullet->getRadian()));
		bullet->setModelMatrix(bullet->getModelMatrix() * Transform2D::Translate(-(bullet->getCenter().x - bullet->getX()), -(bullet->getCenter().y - bullet->getY())));
		RenderMesh2D(bullet->getMesh(), shaders["VertexColor"], bullet->getModelMatrix());
		
		if (countBullet > 0 && j < countBullet) {
			++j;
			++iteratorBullet;
		}
	}
}

void Space::renderMyShip()
{
	//Rotesc Naveta dupa Cursor//
	myShip->setModelMatrix(Transform2D::Translate(myShip->getX(), myShip->getY()));
	myShip->setModelMatrix(myShip->getModelMatrix() * Transform2D::Translate(myShip->getCenter().x - myShip->getX(), myShip->getCenter().y - myShip->getY()));
	myShip->setModelMatrix(myShip->getModelMatrix() * Transform2D::Rotate(myShip->getRadian()));
	myShip->setModelMatrix(myShip->getModelMatrix() * Transform2D::Translate(-(myShip->getCenter().x - myShip->getX()), -(myShip->getCenter().y - myShip->getY())));
	RenderMesh2D(myShip->getMesh(), shaders["VertexColor"], myShip->getModelMatrix());
}

SpaceObject* Space::returnRadian(SpaceObject* myShip, SpaceObject* enemyShip) {
	glm::ivec2 resolution = window->GetResolution();
	if (player->getGameStatus()) {
		deltaTime = enemyShip->getSpeed();
	}
	else {
		enemyShip->setSpeed(0);
	}

	enemyShip->setX(enemyShip->getX() - deltaTime * sin(enemyShip->getRadian()));
	enemyShip->setY(enemyShip->getY() + deltaTime * cos(enemyShip->getRadian()));
	glm::vec3 enemyCenter(enemyShip->getCenter().x - deltaTime * sin(enemyShip->getRadian()), enemyShip->getCenter().y + deltaTime * cos(enemyShip->getRadian()), 0);
	enemyShip->setCenter(enemyCenter);
	enemyShip->setRadian(std::atan2(-(myShip->getCenter().x - enemyShip->getCenter().x),myShip->getCenter().y - enemyShip->getCenter().y));

	return enemyShip;
}

void Space::drowFood() {

	int random = rand() % 3;
	
	float x = rand() % (SpaceX - 200 + 1) + 100;
	float y = rand() % (SpaceY - 200 + 1) + 100;
	this->food = new Food(glm::vec3(x, y, 0));

	if (random == 0) {
		food->setType(type1);
		food->setColor(glm::vec3(1, 0, 1));
	}
	else if (random == 1) {
		food->setType(type2);
		food->setColor(glm::vec3(1, 1, 1));

	}
	else if (random == 2) {
		food->setType(type3);
		food->setColor(glm::vec3(1, 0, 0));
	}
}

void Space::renderFood() {

	RenderMesh2D(food->CreateFood(food->getName(),food->getCenter(),food->getSide(),food->getColor()), shaders["VertexColor"], food->getModelMatrix());
}

