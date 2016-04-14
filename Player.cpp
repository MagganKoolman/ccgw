#include "Player.h"
#include <iostream>

glm::vec3 Player::getLookAt() const {
	return this->mLookat;
}

GameObject* Player::shoot()
{
	return this->mWeapon->shoot(this->mPosition, glm::quat(1.f, 1.f, 1.f, 1.f));
}

void Player::update(const Input* inputs, float dt)
{
	speedY -= 2*dt;
	mSpeed *= abs(1-3*dt);
	glm::vec3 tempLookat = glm::normalize(glm::vec3(mLookat.x, 0, mLookat.z));
	/*if (inputs->keyDown(SDLK_w)) {
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
		speedY += 5;
	}*/

	glm::vec3 dir( 0.0f, 0.0f, 0.0f );
	if( inputs->keyDown( SDLK_w ) )
	{
		mSpeed = mMaxSpeed;
		//mDirection = glm::vec3( cos( mRot ), 0.0f, sin( mRot ) );
		dir += glm::vec3(cos(mRot), 0.0f, sin(mRot));
	}
	if( inputs->keyDown( SDLK_s ) )
	{
		mSpeed = mMaxSpeed;
		float r = glm::pi<float>();
		//mDirection = glm::vec3(cos(mRot - r), 0.0f, sin(mRot - r));
		dir += glm::vec3(cos(mRot - r), 0.0f, sin(mRot - r));
	}
	if( inputs->keyDown( SDLK_a ) )
	{
		mSpeed = mMaxSpeed;
		float r = glm::pi<float>() * 0.5f;
		//mDirection = glm::vec3(cos(mRot - r), 0.0f, sin(mRot - r));
		dir += glm::vec3(cos(mRot - r), 0.0f, sin(mRot - r));
	}
	if( inputs->keyDown( SDLK_d ) )
	{
		mSpeed = mMaxSpeed;
		float r = glm::pi<float>() * 1.5f;
		//mDirection = glm::vec3(cos(mRot-r), 0.0f, sin(mRot-r));
		dir += glm::vec3( cos(mRot-r), 0.0f, sin(mRot-r) );
	}
	if( inputs->keyPressed( SDLK_SPACE  ) )
		 speedY += 5;

	if( glm::length( dir ) > 0.1f )
	{
		dir = glm::normalize( dir );
		mDirection = dir;
	}

	this->mPosition += mDirection * mSpeed * dt + glm::vec3(0, speedY * dt, 0);
	if (mPosition.y < 0.5) {
		mPosition.y = 0.5;
		speedY = 0;
	}
	
	double degree = (inputs->mouseDelta().x)/200 *-1;
	double rad = (inputs->mouseDelta().y) / 400 *-1;

	mRot += degree;
	if( mRot > glm::pi<float>()*2.0f )
		mRot -= glm::pi<float>()*2.0f;
	else if( mRot < 0.0f )
		mRot += glm::pi<float>()*2.0;

	glm::mat4 rotatematrix = {	cosf(degree), 0, sinf(degree),0,
								0,1,0,0,
								-sinf(degree), 0, cosf(degree),0,
								0,0,0,1
								};


	// #fuckedup maths, https://en.wikipedia.org/wiki/Rotation_matrix for formula, might gimbalock??(but probably not)
	glm::vec3 axis = glm::normalize(glm::cross(tempLookat, glm::vec3(0,1,0)));
	glm::mat3 ucm = {	0,-axis.z, axis.y,
						axis.z, 0, -axis.x,
						-axis.y, axis.x, 0};
	glm::mat3 tensorprodU = {	axis.x*axis.x, axis.x*axis.y, axis.x*axis.z,
								axis.y*axis.x, axis.y*axis.y, axis.y*axis.z,
								axis.z*axis.x, axis.z*axis.y, axis.z*axis.z};

	glm::mat3 tempMatrix = cosf(rad)* glm::mat3() + sinf(rad)*ucm + (1 - cosf(rad))*tensorprodU;
	glm::mat4 rotateAroundZ = glm::mat4(
										glm::vec4(tempMatrix[0], 0),
										glm::vec4(tempMatrix[1], 0),
										glm::vec4(tempMatrix[2], 0),
										glm::vec4(0,0,0,1)
										);

	if (glm::dot(glm::vec3(rotateAroundZ * glm::vec4(mLookat, 1)), tempLookat) > 0) {
		this->mLookat = glm::vec3(  rotateAroundZ * glm::vec4(mLookat, 1));
	}

	this->mLookat = glm::vec3(rotatematrix * glm::vec4(mLookat, 1));
	mWorld = rotatematrix * mWorld;
	
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
	mRot = glm::pi<float>() * -0.5f;
}

Player::~Player()
{

}