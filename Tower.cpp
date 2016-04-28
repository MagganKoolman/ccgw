#include "Tower.h"

void Tower::update(std::vector<Enemy*> enemies, const float & dt)
{
	if (mWeaponReady)
	{
		for (int i = 0; i < enemies.size(); i++) {
			if (glm::length(enemies[i]->getPosition() - this->mPosition) < mpWeapon->getRange())
			{
				mWeaponReady = false;
			}
		}
	}
}

Tower::Tower(glm::vec3 position, const Tower &towerRef, float scale): GameObject(position, scale)
{
	this->mpMesh = towerRef.mpMesh;
	this->mpTexture = towerRef.mpTexture;
	this->mpSpecularMap = towerRef.mpSpecularMap;
	this->mpNormalMap = towerRef.mpNormalMap;
	this->mpWeapon = nullptr;
	this->mWeaponReady = true;
}

Tower::Tower()
{
	
}


Tower::~Tower()
{
}
