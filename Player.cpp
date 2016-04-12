#include "Player.h"

void Player::render(const GLuint &programID)
{
	GLuint world = glGetUniformLocation(programID, "world");
	glUniformMatrix4fv(world, 1, GL_FALSE, &this->mWorld[0][0]);
	GLuint texLocation = glGetUniformLocation(programID, "texSampler");
	glUniform1i(texLocation, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mpTexture->getID());
	mpMesh->draw();
}

glm::vec3 Player::getLookAt() const
{
	return mLookAt;
}

void Player::update(const Input* inputs)
{
	if (inputs->keyDown(SDLK_w)) {
		mWorld = glm::translate(mWorld, glm::vec3(0, 0, -0.05));
		mPosition = mPosition + glm::vec3(0, 0, -0.05);
	}
	if (inputs->keyDown(SDLK_s)) {
		mPosition = mPosition + glm::vec3(0, 0, 0.05);
		mWorld = glm::translate(mWorld, glm::vec3(0, 0, 0.05));
	}
	if (inputs->keyDown(SDLK_a)) {
		mPosition = mPosition + glm::vec3(-0.05, 0, 0);
		mWorld = glm::translate(mWorld, glm::vec3(-0.05, 0, 0));
	}
	if (inputs->keyDown(SDLK_d)) {
		mPosition = mPosition + glm::vec3(0.05, 0, 0);
		mWorld = glm::translate(mWorld, glm::vec3(0.05, 0, 0));
	}

}

Player::Player() : GameObject() 
{
	mLookAt = { 0, 0, -1 };
}

Player::~Player()
{

}