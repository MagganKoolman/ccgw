#pragma once
#include "GameObject.h"


class Weapon 
{
public:
	float reloadTime;
	float timeSinceLastShot;
	


private:
	GameObject* shoot(glm::vec3 position, glm::quat rotation);

	Weapon(float rt);
	~Weapon();
};
