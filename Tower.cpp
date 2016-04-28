#include "Tower.h"
#define GLM_FORCE_RADIANS
#include <glm\gtx\vector_angle.hpp>

void Tower::update(Player* enemies, const float & dt)
{
	if (mWeaponReady)
	{	
			glm::vec3 direction = enemies->getPosition() - mPosition;
			mDistanceToTarget = glm::length(direction);
			direction = glm::normalize(direction);
			if (mDistanceToTarget < mRange)
			{
				glm::vec3 rtf = { direction.x, 0, direction.z };
				float rot = glm::angle(rtf, mLookat);
				if (rtf.z > 0.0f)
					rot *= -1.0f;
				mWeaponReady = false;
				mShooting = true;
				mReloadTime = 3;
				mpWeapon->shoot(mPosition, direction, rot + glm::pi<float>() * 0.5, mStrength);
			}	
	}
	else {
		mReloadTime -= mFireRate * dt;
		if (mReloadTime < 0.0)
			mWeaponReady = true;
	}
	if (mShooting) {
		mpWeapon->update(dt);
		mShooting = arrowShot(dt);
	}
}

void Tower::update(std::vector<Enemy*> enemies, const float & dt)
{
	if (mWeaponReady)
	{
		for (int i = 0; i < enemies.size(); i++) {
			glm::vec3 direction = enemies[i]->getPosition() - mPosition;
			mDistanceToTarget = glm::length(direction);
			if (mDistanceToTarget < mpWeapon->getRange())
			{
				mWeaponReady = false;
				mReloadTime = 10;
				mpWeapon->shoot(mPosition, direction, rotX, mStrength);
				break;
			}
		}
	}
	else {
		mReloadTime -= mFireRate * dt;
		if (mReloadTime < 0.0)
			mWeaponReady = true;
	}
	
}

bool Tower::arrowShot(const float &dt) {
	bool targetHit = true;
	mDistanceToTarget -= mStrength * 15 * dt;
	std::cout << mDistanceToTarget << std::endl;
	if (mDistanceToTarget <= 0.0f)
	{
		targetHit = false;	
		//enemy.takeDmg(mstrenght);
	}
	return targetHit;
}
void Tower::render(const GLuint & programID)
{
	GameObject::render(programID);
	if (mShooting)
		mpWeapon->draw(programID);
}

Tower::Tower(GameData* gameData, glm::vec3 position, const Tower &towerRef, float scale): GameObject(position, scale)
{
	this->mpMesh = towerRef.mpMesh;
	this->mpTexture = towerRef.mpTexture;
	this->mpSpecularMap = towerRef.mpSpecularMap;
	this->mpNormalMap = towerRef.mpNormalMap;
	this->mpWeapon = new Weapon(gameData);
	this->mWeaponReady = true;
	mLookat = { 1 ,0, 0 };
	mReloadTime = 5;
	mFireRate = 2;
	mShooting = false;
	mRange = 10;
	mStrength = 2;
}

Tower::Tower()
{
	
}


Tower::~Tower()
{
	delete mpWeapon;
}
