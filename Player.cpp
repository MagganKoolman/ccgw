#include "Player.h"
#include <iostream>
#include "global_variables.h"

glm::vec3 Player::getLookAt() const {
	return this->mLookat;
}

void Player::update(const Input* inputs, const float &dt)
{
	this->mWeapon->update(inputs->buttonDown(0), dt);
	speedY -= 15*dt;
	mSpeed *= abs(1-3*dt);
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
		 speedY += 15;

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

glm::vec2 Player::mousePicking(const glm::vec2 mousePos, const GameData &gameData) {
	float x = (2.0f * mousePos.x) / gWidth - 1.0f;
	float y = 1.0f - (2.0f * mousePos.y) / gHeight;
	glm::vec3 rayNDC = glm::vec3(x, y, 0);
	glm::vec4 rayClipSpace = glm::vec4(rayNDC.x, rayNDC.y, -1.0, 0.0);
	glm::vec4 rayEyeSpace = glm::inverse(gameData.pCamera->getPerspective()) * rayClipSpace;
	rayEyeSpace = glm::vec4(rayEyeSpace.x, rayEyeSpace.y, -1.0, 0.0);
	glm::vec4 rayWorldSpace = glm::inverse(gameData.pCamera->getView()) * rayEyeSpace;
	rayWorldSpace = glm::normalize(rayWorldSpace);
	float scalar = -gameData.pCamera->getPosition().y / rayWorldSpace.y;
	rayWorldSpace *= scalar;
	glm::vec2 pickPos;
	pickPos.x = gameData.pCamera->getPosition().x + rayWorldSpace.x;
	pickPos.y = gameData.pCamera->getPosition().z + rayWorldSpace.z;
	//std::cout << pickPos.x << "    " << pickPos.y << "\n";
	pickPos.x = (int)(pickPos.x + gameData.pGrid->getWidth() / 2);
	pickPos.y = (int)(pickPos.y + gameData.pGrid->getHeight() / 2);
	std::cout << pickPos.x << "    " << pickPos.y << "\n";
	return pickPos;
}

glm::vec3 Player::tacticalUpdate(const Input * inputs, const float &dt, const GameData &gameData)
{
	glm::vec3 dir(0.0f, 0.0f, 0.0f);
	if (inputs->buttonDown(0))
	{
		mSelectedTile = mousePicking(inputs->mousePosition(), gameData);
	}
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
	mSelectedTile = { -1, -1 };
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