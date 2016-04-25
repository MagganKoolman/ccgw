#pragma once
#include "GameObject.h"
#include "Arrow.h"


class Weapon 
{
public:
	void shoot(glm::vec3 position, glm::vec3 lookat, float rotation);

	void draw(const GLuint &programID);
	void update(bool hold, float dt);
	float getStrength() const;
	Weapon(GameData* data);
	~Weapon();

private:
	Arrow *arrows;
	float mStrength;
	int mMax;
};
