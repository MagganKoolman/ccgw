#pragma once

#include "Enemy.h"

class Moleratman : public Enemy
{
public:
	void update();

	Moleratman& operator=( const Moleratman& ref );
	Moleratman( const Moleratman& ref );
	Moleratman();
	~Moleratman();
};