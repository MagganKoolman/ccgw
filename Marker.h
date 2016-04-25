#pragma once
#include "GameObject.h"


class Marker : public GameObject {
public:
	void update(const glm::vec3 &playerPos, const glm::vec3 &lookAt, const float &rot);
	void update(const Input * inputs, const GameData &gameData);
	virtual void render(const GLuint &programID);
	Marker();
	~Marker();
private:
	std::vector<glm::vec2> mMarkedIndex;
	glm::vec2 selectedTile;
	bool mPicked;

	glm::vec2 mousePicking(const glm::vec2 mousePos, const GameData &gameData);
};