#include "Arrow.h"
 
bool Arrow::load(Assets * assets, string texture)
{
	mpTexture = assets->load<Texture>(texture);
	return (mpTexture != nullptr);
}

void Arrow::update(float dt)
{
	
}

Arrow::Arrow(glm::vec3 direction, float travelSpeed, glm::vec3 downVector) 
{
	this->mLookat = direction;
	this->mSpeed = travelSpeed;
	this->mGravitation = downVector;
	
}
Arrow::~Arrow() 
{

}
