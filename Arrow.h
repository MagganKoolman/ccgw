#pragma once

#include "GameObject.h"
#include "Emitter.h"
#include "GameData.h"
#include "BoundingBox.h"

#define MAX_PIERCING_DEPTH 3

class Moleratman;
class Molebat;
class Tower;
class Arrow : public GameObject{
public:
	bool load(GameData* data, string mesh);

	bool isAlive();
	void update(float dt);
	void spawn(bool owner, glm::vec3 position, glm::vec3 direction, float travelSpeed, glm::vec3 downVector, float rotation);
	Arrow();
	~Arrow();

protected:
	GameData* pGameData;

	bool playerOwned;

	float mSpeed;
	glm::vec3 mGravitation;
	float mTimeSinceLastEmmit;
	float mEmmitInterval;

	glm::vec3 mVelocity;
	bool mAlive, mPlayerArrow, mPiercing;

	Molebat* mpPiercedMolebats[MAX_PIERCING_DEPTH];
	Moleratman* mpPiercedMoleratmen[MAX_PIERCING_DEPTH];
	int mPiercings;

	Emitter mEmitter;
};