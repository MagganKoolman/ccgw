#pragma once
#include "GameObject.h"
#include "Arrow.h"


class Weapon 
{
public:
	Arrow* shoot(glm::vec3 position, glm::quat rotation);
	

	void update(float dt);
	Weapon(float rt);
	~Weapon();

private:
	float reloadTime;
	float timeSinceLastShot;

};
