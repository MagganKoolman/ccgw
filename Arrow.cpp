#include "Arrow.h"
 
bool Arrow::load(GameData* data, string mesh)
{
	mpMesh = data->pAssets->load<tempMesh>(mesh);
	bool result = ( mpMesh != nullptr );

	//mpEmitter.load( data, "Models/pns.png" );
	//data->mEmitters.push_back( &mpEmitter );
	
	//pEmitter = data->pEmitter;

	if( data->pEmission->allocEmitter( &mEmitter, 10 ) )
		result = result && mEmitter.load( data, "Models/pns.png" );
	else
		result = false;

	return result;
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

	if( mPosition.y > 0 )
		mEmitter.spawn( mPosition, glm::vec3( 0.0f, 0.1f, 0.0f ), 10.0f, 0.1f, glm::vec2( 0.3f ), glm::vec2( 0.1f ) );
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
