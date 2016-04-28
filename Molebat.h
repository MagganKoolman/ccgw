#pragma once

#include "Enemy.h"
#include "Player.h"
#include "glm\gtx\vector_angle.hpp"

#define MOLEBAT_FAR_DISTANCE 5.0f
#define MOLEBAT_NEAR_DISTANCE 3.0f
#define MOLEBAT_HEIGHT 3.0f
#define MOLEBAT_ALLY_DISTANCE 1.5f

class Molebat : public Enemy
{
public:
	void update();

	void setGameData( GameData* data );

	Molebat& operator=( const Molebat& ref );
	Molebat( const Molebat& ref );
	//Molebat( GameData* data, glm::vec3 position );
	Molebat();
	~Molebat();

private:
	GameData* pGameData;
	int mSin;
};