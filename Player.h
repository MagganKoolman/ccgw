#pragma once
#include "GameObject.h"
#include "Weapon.h"
#include "GameData.h"
#include "Grid.h"

class Player : public GameObject{
public:
	void update(const Input* inputs, const float &dt);
	glm::vec3 tacticalUpdate(const Input* inputs, const float &dt, const GameData &gameData);
	glm::vec3 getMovingDirection(glm::vec3 v1, glm::vec3 v2);
	glm::vec3 getLookAt() const;
	float getRot() const;
	glm::vec2 getSelectedTile() const;
	void render(const GLuint & programID, const glm::mat4 &viewMat);

	Player();
	Player(GameData* data);
	~Player();
private: 
	float speedY;
	float mMaxSpeed;
	float mSpeed;
	glm::vec3 mDirection;
	glm::vec2 mSelectedTile;
	bool mPicked;
	Weapon* mWeapon;

	float mRot;
	glm::vec2 mousePicking(const glm::vec2 mousePos, const GameData &gameData);

 };