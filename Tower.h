#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Player.h"


class Tower : public GameObject
{
public:
	void update(Player* enemies, const float &dt);
	void update(std::vector<Enemy*> enemies, const float &dt);
	void render(const GLuint &programID);
	Tower(GameData* gameData, glm::vec3 position, const Tower &towerRef, float scale);
	Tower();
	~Tower();
private:
	float mFireRate;
	float mReloadTime;
	float mRange;
	Weapon* mpWeapon;
	bool mWeaponReady;
	bool mShooting;
	float mDistanceToTarget;
	float mStrength;
	
	bool arrowShot(const float &dt);
};