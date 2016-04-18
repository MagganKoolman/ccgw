#pragma once

#include "GameObject.h"
#include "Emitter.h"

class Arrow : public GameObject{
public:
	bool load(GameData* data, string mesh);

	bool isAlive();
	void update(float dt);
	void spawn(glm::vec3 position, glm::vec3 direction, float travelSpeed, glm::vec3 downVector);
	Arrow();
	~Arrow();
protected:
	float mSpeed;
	glm::vec3 mGravitation;

	Emitter mpEmitter;
};