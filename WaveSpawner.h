#pragma once

#include "Moleratman.h"
#include "Molebat.h"

#define WAVESPAWNER_DELAY 2.0f

class WaveSpawner
{
public:
	void update( float deltaTime );
	void spawn();
	void incrementWave();

	void setPosition( glm::vec3 position );
	glm::vec3 getPosition() const;

	WaveSpawner& operator=( const WaveSpawner& ref );
	WaveSpawner( const WaveSpawner& ref );
	WaveSpawner( GameData* data );
	~WaveSpawner();

private:
	void spawnMoleratman();
	void spawnMolebat();

	GameData* pGameData;

	int mWave;
	float mDelay;
	glm::vec3 mPosition;

	int mCurMoleratmen, mSpawnMoleratmen;
	int mCurMolebats, mSpawnMolebats;
	int mMoleratmanIndex, mMolebatIndex;

	sNode* mpPath;
	int mTargets;
};