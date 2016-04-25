#pragma once
#include "GameObject.h"


class Marker : public GameObject {
public:

	void update(const glm::vec3 &playerPos, const glm::vec3 &lookAt, const float &rot);
	void update(const glm::vec2 &mousePos, const glm::vec3 cameraPos);
	Marker();
	~Marker();
private:
	
};