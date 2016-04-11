#include "Weapon.h"

GameObject* Weapon::shoot(glm::vec3 position, glm::quat rotation) 
{
	GameObject* projectile = nullptr; // = new Arrow();
	return projectile;
}


Weapon::Weapon(float rt) 
{
	this->reloadTime = rt;
	this->timeSinceLastShot = 0;
}

Weapon::~Weapon() 
{

}