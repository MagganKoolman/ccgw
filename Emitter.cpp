#include "Emitter.h"

bool Emitter::load( Assets* assets, string texture )
{
	bool result = true;

	mpParticles = new Particle[mMax];

	for( int i=0; i<mMax; i++ )
		result = result && mpParticles[i].load( assets, texture );

	return result;
}

void Emitter::spawn( glm::vec3 velocity, float lifetime, glm::vec2 startScale, glm::vec2 endScale, float drag )
{
	for( int i=0; i<mMax; i++ )
		if( mpParticles[i].getLifetime() <= mpParticles[i].getElapsed() )
			mpParticles[i].spawn( mPosition, velocity, lifetime,startScale, endScale, drag );
}

void Emitter::update( float deltaTime )
{
	for( int i=0; i<mMax; i++ )
		mpParticles[i].update( deltaTime );
}

void Emitter::draw()
{
	for( int i=0; i<mMax; i++ )
		mpParticles[i].draw();
}

void Emitter::setPosition( glm::vec3 position )
{
	mPosition = position;
}

glm::vec3 Emitter::getPosition() const
{
	return mPosition;
}

Emitter& Emitter::operator=( const Emitter& ref )
{
	if( mpParticles )
		delete[] mpParticles;

	mMax = ref.mMax;
	mpParticles = new Particle[mMax];
	for( int i=0; i<mMax; i++ )
		mpParticles[i] = ref.mpParticles[i];

	return *this;
}

Emitter::Emitter( const Emitter& ref )
	: mMax( ref.mMax )
{
	mpParticles = new Particle[mMax];
	for( int i=0; i<mMax; i++ )
		mpParticles[i] = ref.mpParticles[i];
}

Emitter::Emitter( int maxParticles )
	: mMax( maxParticles ), mpParticles( nullptr )
{
}

Emitter::~Emitter()
{
	if( mpParticles )
		delete[] mpParticles;
}