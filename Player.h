#pragma once
#include "GameObject.h"
#include "Weapon.h"

class Player : public GameObject{
public:
	void update(const Input* inputs);
	bool load(tempMesh* assets);
	void render(const GLuint &programID);
	glm::vec3 getLookAt() const;

	Player();
	~Player();
private: 
	Weapon* mWeapon;
	glm::vec3 mLookAt;
 };