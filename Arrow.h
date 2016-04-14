#pragma once

#include "GameObject.h"


class Arrow : public GameObject{
public:
	bool load(Assets* assets, string texture);

	void update(float dt);
	Arrow(glm::vec3 direction, float travelSpeed, glm::vec3 downVector);
	~Arrow();
protected:
	int mSpeed;
	glm::vec3 mGravitation;
};