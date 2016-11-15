#include <Core/Engine.h>
#include <Tema1\Bullet.h>

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

Bullet::Bullet(glm::vec3 center)
{ 
	this->setName(bulletName);
	this->setSide(bulletSide);
	this->setType(bulletType);
	this->setColor(bulletColor);
	this->setCenter(center);
}

Mesh * SpaceObject::CreateBullet(std::string name, glm::vec3 bulletCenter, int length, glm::vec3 color)
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(bulletCenter + glm::vec3(-length / 4, -length, 0), color),
		VertexFormat(bulletCenter + glm::vec3(length / 4, -length, 0), color),
		VertexFormat(bulletCenter + glm::vec3(length / 4, length, 0), color),
		VertexFormat(bulletCenter + glm::vec3(-length / 4,  length, 0), color),

	};

	Mesh* bullet = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	indices.push_back(0);
	indices.push_back(2);

	bullet->InitFromData(vertices, indices);
	return bullet;
}


