#include "Weapon.h"

Arrow* Weapon::shoot(glm::vec3 position, glm::quat rotation) 
{
	Arrow* projectile = nullptr;
	if (timeSinceLastShot > reloadTime) {
		timeSinceLastShot = 0;
		projectile =  new Arrow(glm::vec3(1,0,0),2, glm::vec3(0,-1,0));
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