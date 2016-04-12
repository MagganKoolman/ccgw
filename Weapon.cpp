#include "Weapon.h"

GameObject* Weapon::shoot(glm::vec3 position, glm::quat rotation) 
{
	GameObject* projectile = nullptr;
	if (timeSinceLastShot > reloadTime) {
		timeSinceLastShot = 0;
		projectile = nullptr; // = new Arrow();
	}
	return projectile;
}
void Weapon::update(float dt) {
	this->timeSinceLastShot += dt;
}


Weapon::Weapon(float rt) 
{
	this->reloadTime = rt;
	this->timeSinceLastShot = 0;
}

Weapon::~Weapon() 
{

}