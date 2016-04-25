#include "Arrow.h"
#define GLM_FORCE_RADIANS
#include "glm\gtx\vector_angle.hpp"

 
bool Arrow::load(GameData* data, string mesh)
{
	mpMesh = data->pAssets->load<tempMesh>(mesh);
	bool result = ( mpMesh != nullptr );

	//mpEmitter.load( data, "Models/pns.png" );
	//data->mEmitters.push_back( &mpEmitter );
	
	//pEmitter = data->pEmitter;

	if( data->pEmission->allocEmitter( &mEmitter, 100 ) )
		result = result && mEmitter.load( data, "Models/pns.png" );
	else
		result = false;

	return result;
}

bool Arrow::isAlive() 
{
	return mPosition.y > -1;
}
void Arrow::update(float dt)
{
	this->mTimeSinceLastEmmit += dt;

	glm::vec3 tempVec = glm::normalize(glm::vec3(mLookat.x, 0, mLookat.z));
	this->rotY = glm::angle(mLookat, tempVec);
	if (mLookat.y < 0) {
		rotY *= -1;
	}
	this->mPosition += mSpeed*mLookat*dt;

	/*
	glm::mat3 rotationY = glm::mat3(
		cosf(rotX), 0, sinf(rotX),
		0, 1, 0,
		-sinf(rotX), 0, cosf(rotX));
	glm::mat3 rotationX = glm::mat3(1, 0, 0,
		0, cosf(rotY), sinf(rotY),
		0, -sinf(rotY), cosf(rotY));

	glm::mat3 totalRotation = rotationX * rotationY;
	this->mWorld = glm::mat4(glm::vec4(totalRotation[0], 0),
		glm::vec4(totalRotation[1], 0),
		glm::vec4(totalRotation[2], 0),
		glm::vec4(mPosition.x, mPosition.y, mPosition.z, 1));
	*/
	/*
	glm::mat3 rotationY = glm::mat3(
		cosf(rotY), 0, sinf(rotY),
		0, 1, 0,
		-sinf(rotY), 0, cosf(rotY));
	glm::mat3 rotationX = glm::mat3(1,0,0,
									0,	cosf(rotX - glm::pi<float>()*0.5f), sinf(rotX - glm::pi<float>()*0.5f),
									0,	-sinf(rotX - glm::pi<float>()*0.5f), cosf(rotX - glm::pi<float>()*0.5f));

	glm::mat3 totalRotation = rotationY * rotationX;
	this->mWorld = glm::mat4(glm::vec4(totalRotation[0], 0),
		glm::vec4(totalRotation[1], 0),
		glm::vec4(totalRotation[2], 0),
		glm::vec4(mPosition.x, mPosition.y, mPosition.z, 1));
	*/
	/*
	this->mWorld = {
		cosf(rotX),				sinf(rotY)*sinf(rotX),		sinf(rotX),				0,
		0,						cosf(rotX),					sinf(rotX),				0,
		sinf(rotX),				cosf(rot)*sinf(rotX)*-1.f,	cosf(rotY)*cosf(rotX),	0,
		mPosition.x,			mPosition.y,				mPosition.z,			1
	};*/
	
	float p = glm::pi<float>() * 0.5f;
	this->mWorld = {
					cosf(rotY)* cosf(rotX),		sinf(rotY),		cosf(rotY ) * sinf(rotX),	0,
					-sinf(rotY) * cosf(rotX),	cosf(rotY),		-sinf(rotY) * sinf(rotX),	0,
					-sinf(rotX),				0,				cosf(rotX),					0,
					mPosition.x,				mPosition.y,	mPosition.z,				1
	};

	this->mLookat = glm::normalize((this->mLookat*this->mSpeed) + 5.f*mGravitation*dt);

	if (mTimeSinceLastEmmit > mEmmitInterval)
	{
		mEmitter.spawn(mPosition, glm::vec3(0.0f, 0.1f, 0.0f), 2.f, 0.1f, glm::vec2(0.3f), glm::vec2(0.1f));
		mTimeSinceLastEmmit = 0;
	}
}
Arrow::Arrow() : GameObject({0,-10,0})
{
	this->rotX = 0;
	this->mEmmitInterval = 0.1;
	this->mTimeSinceLastEmmit = 0;
	this->mLookat = {1,0,0};
	this->mSpeed = 1.f;
	this->mGravitation = {0,-1,0};
	this->mpSpecularMap = nullptr;
	this->mpNormalMap = nullptr;
}

void Arrow::spawn(glm::vec3 position, glm::vec3 direction, float travelSpeed, glm::vec3 downVector, float rotation)
{
	this->rotY = 0;
	this->rotX = rotation;
	this->mPosition = position;
	this->mLookat = direction;
	this->mSpeed = travelSpeed;
	this->mGravitation = downVector;
}
Arrow::~Arrow() 
{
	
}
