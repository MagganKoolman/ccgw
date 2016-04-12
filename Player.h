#pragma once
#include "GameObject.h"
#include "Weapon.h"

class Player : public GameObject{
public:
	void update(Input* inputs, float dt);
	bool load(tempMesh* assets);
	void render(const GLuint &programID);

	Player();
	~Player();
private: 
	float mMaxSpeed;
	float mSpeed;
	glm::vec3 mDirection;
	Weapon* mWeapon;
 };