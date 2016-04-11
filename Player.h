#pragma once
#include "GameObject.h"
#include "Weapon.h"

class Player : public GameObject{
public:
	void update(const Input* inputs);
	bool load(tempMesh* assets);
	void render(const GLuint &programID);

	Player();
	~Player();
private: 
	Weapon* mWeapon;
 };