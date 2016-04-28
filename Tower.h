#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Weapon.h"


class Tower : public GameObject
{
public:

	void update(std::vector<Enemy*> enemies, const float &dt);
	bool shotFired(const float &dt);
	Tower(glm::vec3 position, const Tower &towerRef, float scale);
	Tower();
	~Tower();
private:
	float mFireRate;
	float mTimeSinceLastShot;
	Weapon* mpWeapon;
	bool mWeaponReady;
	
};