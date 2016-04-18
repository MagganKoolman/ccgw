#pragma once
#include "GameObject.h"
#include "Arrow.h"


class Weapon 
{
public:
	void shoot(glm::vec3 position, glm::vec3 lookat);

	void draw(const GLuint &programID);
	void update(float dt);
	Weapon(float rt, GameData* data);
	~Weapon();

private:
	Arrow arrows[10];
	float mReloadTime;
	float mTimeSinceLastShot;
	int mMax;
};
