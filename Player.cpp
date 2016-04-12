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

glm::vec3 Player::getLookAt() const
{
	return mLookAt;
}

void Player::update(const Input* inputs)
{
	if (inputs->keyDown(SDLK_w)) {
		mWorld = glm::translate(mWorld, glm::vec3(0, 0.001, 0));
		mPosition = mPosition + glm::vec3(0, 0.001, 0);
	}
	if (inputs->keyDown(SDLK_s)) {
		mPosition = mPosition + glm::vec3(0, -0.001, 0);
		mWorld = glm::translate(mWorld, glm::vec3(0, -0.001, 0));
	}

}

Player::Player() : GameObject() 
{
	mLookAt = { 0, 0, 1 };
}

Player::~Player()
{

}