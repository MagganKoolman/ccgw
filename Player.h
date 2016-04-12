#pragma once
#include "GameObject.h"
#include "Weapon.h"

class Player : public GameObject{
public:
	void update(const Input* inputs, float dt);
	glm::vec3 getMovingDirection(glm::vec3 v1, glm::vec3 v2);
	bool load(tempMesh* assets);
	void render(const GLuint &programID);
	glm::vec3 getLookAt() const;

	Player();
	~Player();
private: 
	float speedY;
	float mMaxSpeed;
	float mSpeed;
	glm::vec3 mDirection;
	Weapon* mWeapon;
 };