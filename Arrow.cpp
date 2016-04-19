#include "Arrow.h"
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
	this->rotY = glm::radians(glm::angle(mLookat, tempVec));
	if (mLookat.y < 0) {
		rotY *= -1;
	}

	this->mPosition += mSpeed*mLookat*dt;

	this->mWorld = {
					cosf(rotY)* cosf(rotX),		sinf(rotY),		cosf(rotY) * sinf(rotX),	0,
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
Arrow::Arrow() : GameObject({0,-1,0})
{
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
