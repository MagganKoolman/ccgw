#pragma once

#include "Enemy.h"

class Moleratman : public Enemy
{
public:
	Moleratman& operator=( const Moleratman& ref );
	Moleratman( const Moleratman& ref );
	Moleratman();
	~Moleratman();
};