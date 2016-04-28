#include "Player.h"
#include <iostream>
#include "global_variables.h"
#include "Grid.h"

glm::vec3 Player::getLookAt() const {
	return this->mLookat;
}

float Player::getRot() const
{
	return rotX;
}

void Player::update(const Input* inputs, const float &dt)
{
	this->mWeapon->update(inputs->buttonDown(0), dt);
	speedY -= 15*dt;
	//mSpeed *= abs(1-3*dt);
	mSpeed = 0;
	glm::vec3 tempLookat = glm::normalize(glm::vec3(mLookat.x, 0, mLookat.z));
	glm::vec3 dir( 0.0f, 0.0f, 0.0f );

	if( inputs->keyDown( SDLK_w ) )
	{
		mSpeed = mMaxSpeed;
		dir += glm::vec3(cos(rotX), 0.0f, sin(rotX));
	}
	if( inputs->keyDown( SDLK_s ) )
	{
		mSpeed = mMaxSpeed;
		float r = glm::pi<float>();
		dir += glm::vec3(cos(rotX - r), 0.0f, sin(rotX - r));
	}
	if( inputs->keyDown( SDLK_a ) )
	{
		mSpeed = mMaxSpeed;
		float r = glm::pi<float>() * 0.5f;
		dir += glm::vec3(cos(rotX - r), 0.0f, sin(rotX - r));
	}
	if( inputs->keyDown( SDLK_d ) )
	{
		mSpeed = mMaxSpeed;
		float r = glm::pi<float>() * 1.5f;
		dir += glm::vec3( cos(rotX -r), 0.0f, sin(rotX -r) );
	}
	if( inputs->keyPressed( SDLK_SPACE  ) )
		 speedY += 10;

	if( glm::length( dir ) > 0.1f )
	{
		dir = glm::normalize( dir );
		mDirection = dir;
	}

	float dy = speedY * dt;
	int xStart = (this->mPosition.x + mDirection.x * mSpeed * dt) / mGameData->boxScale;
	int yStart =(this->mPosition.z + mDirection.z * mSpeed * dt)/ mGameData->boxScale;
	bool intersect = false;
	mBB.center = this->mPosition;

	int x = (int)((int)(this->mPosition.x + 1.0f) / mGameData->boxScale);
	int y = (int)((int)(this->mPosition.z + 1.0f) / mGameData->boxScale);
	std::cout << x << "  " << y << std::endl;
	if (!(y < 0 || x < 0 || y >= mGameData->pGrid->getWidth() || x >= mGameData->pGrid->getHeight()))
		if (mGameData->pGrid->getTile(x, y) != TILE_EMPTY)
			if(this->mBB.intersect(glm::vec3(x*mGameData->boxScale, 1 , y*mGameData->boxScale), mGameData->boxScale/2))
				//std::cout << "COLLISON" << x*mGameData->boxScale << "  " << y*mGameData->boxScale;
	std::cout << std::endl;
	if (inputs->keyPressed(SDLK_q) ){
		for (int i = 0; i < mGameData->pGrid->getHeight(); i++) {
			for (int j = 0; j < mGameData->pGrid->getWidth();j++) {
				std::cout << (int)mGameData->pGrid->getTile(j, i);
			}
		std::cout << endl;
		}
		int a = 0;
	}
	/*
	for (int i = -1; i <= 1 && !intersect; i++) {
		for (int j = -1; j <= 1 && !intersect; j++) {
			int x = (int)((int)(this->mPosition.x + 1.0f) / mGameData->boxScale) + i;
			int y = (int)((int)(this->mPosition.z + 1.0f) / mGameData->boxScale) + j;
			if (!(y < 0 || x < 0 || y >= (int)mGameData->pGrid->getHeight() || x >= (int)mGameData->pGrid->getWidth()))
				if (mGameData->pGrid->getTile(x, y) != 0)
					std::cout << "COLLISION" << x << "  "<< y;
					//intersect = this->mBB.intersect(glm::vec3(x*mGameData->boxScale, 0, y*mGameData->boxScale), mGameData->boxScale);
		}
	}
	*/

	if (!intersect) {
		this->mPosition += mDirection * mSpeed * dt + glm::vec3(0, dy, 0);

	}


	if (mPosition.y < 0.5) {
		mPosition.y = 0.5;
		speedY = 0;
	}
	
	double degree = (inputs->mouseDelta().x)/200 *-1;
	double rad = (inputs->mouseDelta().y) / 400 *-1;

	rotX += degree;
	if(rotX > glm::pi<float>()*2.0f )
		rotX -= glm::pi<float>()*2.0f;
	else if(rotX < 0.0f )
		rotX += glm::pi<float>()*2.0;

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

	//mLookat = glm::rotate(glm::quat(cosf(mRot),0,sinf(mRot),0), glm::vec3(0,1));

	//this->mRotation.z = 
	this->mLookat = glm::vec3(rotatematrix * glm::vec4(mLookat, 1));
	mWorld = rotatematrix * mWorld;
	
	mWorld[3][0] = mPosition.x;
	mWorld[3][1] = mPosition.y;
	mWorld[3][2] = mPosition.z;
	mWorld[3][3] = 1.f;

	if (inputs->buttonReleased(0))
		mWeapon->shoot(this->mPosition, mLookat, rotX);
}

glm::vec3 Player::tacticalUpdate(const Input * inputs, const float &dt, const GameData &gameData)
{
	glm::vec3 dir(0.0f, 0.0f, 0.0f);	
	if (inputs->keyDown(SDLK_w))
	{
		dir += glm::vec3(0.0f, 0.0f, -10.0 * dt);
	}
	if (inputs->keyDown(SDLK_s))
	{
		dir += glm::vec3(0.0f, 0.0f, 10.0 * dt);
	}
	if (inputs->keyDown(SDLK_a))
	{
		dir += glm::vec3(-10.0 * dt, 0.0f, 0.0f);
	}
	if (inputs->keyDown(SDLK_d))
	{
		dir += glm::vec3(10.0 * dt, 0.0f, 0.0f);
	}
	return dir;
}

void Player::render(const GLuint & programID, const glm::mat4 &viewMat)
{
	GameObject::render(programID, viewMat);
	this->mWeapon->draw(programID);
}

glm::vec3 Player::getMovingDirection(glm::vec3 v1, glm::vec3 v2) {
	glm::vec3 result = glm::normalize(v1 + v2);
	if (result != result)
 		result = glm::vec3(0,0,0);
	return result;
}

Player::Player() 
{}

Player::Player(GameData* data) : GameObject()
{
	this->mGameData = data;
	mWeapon = new Weapon(data);
	mWorld = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	mMaxSpeed = 10;
	speedY = 0;
	rotX = glm::pi<float>() * -0.5f;
}

Player::~Player()
{
	delete mWeapon;
}