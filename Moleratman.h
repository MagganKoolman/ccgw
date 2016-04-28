#pragma once

#include "Enemy.h"

#define MOLERATMAN_SPEED 0.05f

class Moleratman : public Enemy
{
public:
	void update();

	Moleratman& operator=( const Moleratman& ref );
	Moleratman( const Moleratman& ref );
	Moleratman();
	~Moleratman();
};