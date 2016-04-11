#pragma once
#include "GameObject.h"

class Player : public GameObject{
public:
	void update(Input* input);
	bool load(Assets* assets);
	void render();

	Player();
	~Player();
private: 
	
 };