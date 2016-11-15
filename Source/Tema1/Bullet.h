#pragma once
#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <Tema1\SpaceObject.h>

using namespace std;

class Bullet : public SpaceObject
{
	public:
		Bullet();
		Bullet(glm::vec3 center);
		~Bullet();

	private:
		string bulletName;
		string bulletType = "bullet";
		int bulletSide = 10;
		glm::vec3 bulletColor = glm::vec3(0, 1, 0);
};