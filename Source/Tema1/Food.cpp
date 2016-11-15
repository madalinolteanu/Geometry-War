#include <Core/Engine.h>
#include <Tema1\Food.h>

Food::Food()
{
}

Food::~Food()
{
}

Food::Food(glm::vec3 center) {

	this->setCenter(center);
	this->setSide(side);
	this->setName(name);
}

Mesh * SpaceObject::CreateFood(std::string name, glm::vec3 foodCenter, int length, glm::vec3 color)
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(foodCenter + glm::vec3(-length, -length, 0), color),
		VertexFormat(foodCenter + glm::vec3(length, -length, 0), color),
		VertexFormat(foodCenter + glm::vec3(length, length, 0), color),
		VertexFormat(foodCenter + glm::vec3(-length,  length, 0), color),

	};

	Mesh* food = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	indices.push_back(0);
	indices.push_back(2);

	food->InitFromData(vertices, indices);
	return food;
}