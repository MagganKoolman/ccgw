#pragma once
#include "GameObject.h"
#include "Weapon.h"
#include "GameData.h"

class Player : public GameObject{
public:
	void update(const Input* inputs, float dt);
	glm::vec3 getMovingDirection(glm::vec3 v1, glm::vec3 v2);
	glm::vec3 getLookAt() const;
	void shoot();
	void render(const GLuint & programID, const glm::mat4 &viewMat);

	Player();
	Player(GameData* data);
	~Player();
private: 
	float speedY;
	float mMaxSpeed;
	float mSpeed;
	glm::vec3 mDirection;
	Weapon* mWeapon;

	float mRot;
 };