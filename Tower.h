#pragma once
#include "GameObject.h"


class Tower : public GameObject
{
public:

	
	Tower(glm::vec3 position, const Tower &towerRef, float scale);
	Tower();
	~Tower();
private:
	float mFireRate;
	float mTimeSinceLastShot;
	
};