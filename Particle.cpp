#include "Particle.h"

bool Particle::load( Assets* assets, string texture )
{
	mpTexture = assets->load<Texture>( texture );
	return ( mpTexture != nullptr );
}

void Particle::spawn( glm::vec3 position, glm::vec3 velocity, float lifetime, glm::vec2 startScale, glm::vec2 endScale, float drag )
{
	mPosition = position;
	mVelocity = velocity;
	mLifetime = lifetime;
	mStartScale = mScale = startScale;
	mEndScale = endScale;
	mDrag = drag;
	mElapsed = 0.0f;
}

void Particle::update( float deltaTime )
{
	if( mLifetime > 0.0f )
	{
		mPosition += mVelocity;
		mVelocity *= 1.0f - mDrag;
	
		float a = mElapsed / mLifetime;
		mScale = ( mStartScale * a ) + ( ( 1-a ) * mEndScale );

		mElapsed += deltaTime;
	}
}

void Particle::draw()
{

}

float Particle::getLifetime() const
{
	return mLifetime;
}

float Particle::getElapsed() const
{
	return mElapsed;
}

Particle& Particle::operator=( const Particle& ref )
{
	mPosition = ref.mPosition;
	mVelocity = ref.mVelocity;
	mScale = ref.mScale;

	mStartScale = ref.mStartScale;
	mEndScale = ref.mEndScale;

	mLifetime = ref.mLifetime;
	mElapsed = ref.mElapsed;
	mDrag = ref.mDrag;

	mpTexture = ref.mpTexture;
	return *this;
}

Particle::Particle( const Particle& ref )
	: mPosition( ref.mPosition ), mVelocity( ref.mVelocity ), mScale( ref.mScale ),
	mStartScale( ref.mStartScale ), mEndScale( ref.mEndScale ),
	mLifetime( ref.mLifetime ), mElapsed( ref.mElapsed ), mDrag( ref.mDrag ),
	mpTexture( ref.mpTexture )
{
}

Particle::Particle()
	: mPosition( 0.0f ), mVelocity( 0.0f ), mScale( 1.0f ),
	mStartScale( 1.0f ), mEndScale( 1.0f ),
	mLifetime( 0.0f ), mElapsed( 0.0f ), mDrag( 0.0f ),
	mpTexture( nullptr )
{
}

Particle::~Particle()
{
}