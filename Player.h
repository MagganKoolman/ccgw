#pragma once
#include "GameObject.h"
#include "Weapon.h"

class Player : public GameObject{
public:
	void update(Input* input);
	bool load(Assets* assets);
	void render();

	Player();
	~Player();
private: 
	Weapon* mWeapon;
 };