#include "Player.h"

bool Player::load(tempMesh* assets) 
{
	mpMesh = assets;
	return (mpMesh != nullptr);
}

void Player::render(const GLuint &programID)
{
	GLuint world = glGetUniformLocation(programID, "world");
	glUniformMatrix4fv(world, 1, GL_FALSE, &this->mWorld[0][0]);
	mpMesh->draw();
}

void Player::update(Input* inputs, float dt)
{
	mSpeed *= abs(1-dt);
	glm::vec3 tempLookat = glm::normalize(glm::vec3(mLookat.x, 0, mLookat.z));
	if (inputs->keyDown(SDLK_w)) {
		this->mSpeed = mMaxSpeed;
		this->mDirection = glm::normalize(mDirection + tempLookat);
	}
	if (inputs->keyDown(SDLK_s)) {
		this->mSpeed = mMaxSpeed;
		this->mDirection = glm::normalize(mDirection - tempLookat);
	}
	if (inputs->keyDown(SDLK_a)) {
		this->mSpeed = mMaxSpeed;
		this->mDirection = glm::normalize(mDirection + glm::cross(glm::vec3(0,1,0), tempLookat));
	}
	if (inputs->keyDown(SDLK_d)) {
		this->mSpeed = mMaxSpeed;
		this->mDirection = glm::normalize(mDirection + glm::cross(tempLookat, glm::vec3(0, 1, 0)));
	}
	if (inputs->keyPressed(SDLK_SPACE)) {
		this->mDirection = glm::normalize(mDirection + glm::vec3(0, 1, 0));
	}
	this->mPosition += mDirection * mSpeed * dt;
	
}

Player::Player() : GameObject() 
{
	mWorld = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	mMaxSpeed = 1;
}

Player::~Player()
{

}