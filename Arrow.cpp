#include "Arrow.h"
 
bool Arrow::load(Assets * assets, string mesh)
{
	mpMesh = assets->load<tempMesh>(mesh);
	return (mpTexture != nullptr);
}

bool Arrow::isAlive() 
{
	return mPosition.y > 0;
}
void Arrow::update(float dt)
{
	this->mLookat = glm::normalize((this->mLookat*this->mSpeed) + this->mGravitation*dt);
	this->mPosition += mSpeed*mLookat*dt;
	this->mWorld[3][0] = mPosition.x;
	this->mWorld[3][1] = mPosition.y;
	this->mWorld[3][2] = mPosition.z;
}
Arrow::Arrow() : GameObject({0,-1,0})
{
	this->mLookat = {1,0,0};
	this->mSpeed = 1.f;
	this->mGravitation = {0,-1,0};
}


void Arrow::spawn(glm::vec3 position, glm::vec3 direction, float travelSpeed, glm::vec3 downVector)
{
	this->mPosition = position;
	this->mLookat = direction;
	this->mSpeed = travelSpeed;
	this->mGravitation = downVector;
}
Arrow::~Arrow() 
{

}
