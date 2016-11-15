#pragma once
#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <Tema1\SpaceObject.h>

class Food : public SpaceObject
{
	public:
		Food();
		~Food();
		Food(glm::vec3 center);

	private:
		int side = 6;
		std::string name = "food";
};