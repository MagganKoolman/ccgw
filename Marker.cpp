#include "Marker.h"
#include "Player.h"

void Marker::update(const glm::vec3 &playerPos, const glm::vec3 &lookAt, const float &rot) {
	float aRot = rot + glm::pi<float>() * 0.5f;
	this->mWorld = {
		cosf(aRot), 0.0f, sinf(aRot), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sinf(aRot), 0.0f, cosf(aRot), 0.0f,
		playerPos.x + lookAt.x * 8,			playerPos.y + lookAt.y * 8,	playerPos.z + lookAt.z * 8,	1
	};
}

void Marker::update(const glm::vec2 &tileIndex, const glm::vec3 cameraPos)
{
	mWorld[3][0] = tileIndex.x;
	mWorld[3][1] = 1.0f;
	mWorld[3][2] = tileIndex.y;
}

Marker::Marker()
{

}

Marker::~Marker()
{

}
