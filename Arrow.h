#pragma once

#include "GameObject.h"


class Arrow : public GameObject{
public:
	void update(Input* input);
	Arrow(int travelSpeed, glm::vec3 downVector);
	~Arrow();
protected:
	int mSpeed;
	glm::vec3 mGravitation;
};