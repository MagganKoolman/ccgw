#include "Player.h"
#include <iostream>

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
glm::vec3 Player::getLookAt() const {
	return this->mLookat;
}
void Player::update(const Input* inputs, float dt)
{
	speedY -= dt;
	mSpeed *= abs(1-3*dt);
	glm::vec3 tempLookat = glm::normalize(glm::vec3(mLookat.x, 0, mLookat.z));
	if (inputs->keyDown(SDLK_w)) {
		this->mSpeed = mMaxSpeed;
		this->mDirection = getMovingDirection(mDirection, tempLookat);
	}
	if (inputs->keyDown(SDLK_s)) {
		this->mSpeed = mMaxSpeed; 
		this->mDirection = getMovingDirection(mDirection, -tempLookat);
	}
	if (inputs->keyDown(SDLK_a)) {
		this->mSpeed = mMaxSpeed;
		this->mDirection = getMovingDirection(mDirection, glm::cross(glm::vec3(0, 1, 0), tempLookat));
	}
	if (inputs->keyDown(SDLK_d)) {
		this->mSpeed = mMaxSpeed;
		this->mDirection = getMovingDirection(mDirection, glm::cross(tempLookat, glm::vec3(0, 1, 0)));
	}
	if (inputs->keyPressed(SDLK_SPACE)) {
		speedY += 1;
	}
	this->mPosition += mDirection * mSpeed * dt + glm::vec3(0, speedY * dt, 0);
	if (mPosition.y < 0.5) {
		mPosition.y = 0.5;
		speedY = 0;
	}
	
	float degree = (inputs->mouseDelta().x)/200 *-1;
	float rad = (inputs->mouseDelta().y) / 400 *-1;


	glm::mat4 rotatematrix = {	cosf(degree), 0, sinf(degree),0,
								0,1,0,0,
								-sinf(degree), 0, cosf(degree),0,
								0,0,0,1
								};

	glm::vec3 axis = glm::cross(tempLookat, glm::vec3(0,1,0));
	glm::mat3 ucm = {	0,-axis.z, axis.y,
						axis.z, 0, -axis.x,
						-axis.y, axis.x, 0};
	glm::mat4 rotateAroundZ = glm::mat4();//cosf(rad)* glm::mat4() + sinf(rad)
								/*{ cosf(rad) + axis.x*axis.x*(1-cosf(rad)), axis.x*axis.y*(1-cosf(rad)) - axis.z*sinf(rad), axis.x*axis.zsinf(rad),0,0,
								-sinf(rad), cosf(rad),0,0,
								0,0,1,0,
								0,0,0,1
								};*/

	this->mLookat = glm::vec3((rotateAroundZ *rotatematrix) * glm::vec4(mLookat,1) );
	mWorld =  rotatematrix * mWorld;
	
	mWorld[3][0] = mPosition.x;
	mWorld[3][1] = mPosition.y;
	mWorld[3][2] = mPosition.z;
	mWorld[3][3] = 1.f;


}
glm::vec3 Player::getMovingDirection(glm::vec3 v1, glm::vec3 v2) {
	glm::vec3 result = glm::normalize(v1 + v2);
	if (result != result)
 		result = glm::vec3(0,0,0);
	return result;
}

Player::Player() : GameObject() 
{
	mWorld = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	mMaxSpeed = 3;
	speedY = 0;
}

Player::~Player()
{

}