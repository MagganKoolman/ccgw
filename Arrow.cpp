#include "Arrow.h"
 
bool Arrow::load(GameData* data, string mesh)
{
	mpMesh = data->pAssets->load<tempMesh>(mesh);

	mpEmitter.load( data, "Models/pns.png" );
	data->mEmitters.push_back( &mpEmitter );

	return (mpTexture != nullptr);
}

bool Arrow::isAlive() 
{
	return mPosition.y > -1;
}
void Arrow::update(float dt)
{
	this->mLookat = glm::normalize((this->mLookat*this->mSpeed) + mGravitation*dt);
	this->mPosition += mSpeed*mLookat*dt;
	this->mWorld[3][0] = mPosition.x;
	this->mWorld[3][1] = mPosition.y;
	this->mWorld[3][2] = mPosition.z;

	mpEmitter.setPosition(mPosition);
	mpEmitter.spawn(glm::vec3(0.0f, -0.05f, 0.0f), 10.0f, 0.1f, glm::vec2(0.3f), glm::vec2(0.1f));
	mpEmitter.update(dt);
}
Arrow::Arrow() : GameObject({0,-1,0}), mpEmitter( 300 )
{
	this->mLookat = {1,0,0};
	this->mSpeed = 1.f;
	this->mGravitation = {0,-1,0};
}


void Arrow::spawn(glm::vec3 position, glm::vec3 direction, float travelSpeed, glm::vec3 downVector, float rotation)
{
	//this->mRotation = rotation;
	this->mPosition = position;
	this->mLookat = direction;
	this->mSpeed = travelSpeed;
	this->mGravitation = downVector;
}
Arrow::~Arrow() 
{
	
}
