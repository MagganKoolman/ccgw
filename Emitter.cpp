#include "Emitter.h"

bool Emitter::load( GameData* data, string texture )
{
	bool result = true;

	mpCamera = data->pCamera;
	mpBillboardProgram = data->pBillboardProgram;

	mpParticles = new Particle[mMax];
	mpSorted = new Particle*[mMax];
	mDistances = new float[mMax];

	for( int i=0; i<mMax; i++ )
		result = result && mpParticles[i].load( data, texture );

	return result;
}

void Emitter::spawn( glm::vec3 velocity, float lifetime, float drag, glm::vec2 startScale, glm::vec2 endScale )
{
	for( int i=0; i<mMax; i++ )
	{
		if( mpParticles[i].getLifetime() <= mpParticles[i].getElapsed() )
		{
			mpParticles[i].spawn( mPosition, velocity, lifetime, drag, startScale, endScale );
			mpSorted[mAlive++] = &mpParticles[i];
			break;
		}
	}
}

void Emitter::update( float deltaTime )
{
	glm::vec3 cameraPosition = mpCamera->getPosition();
	for( int i=0; i<mMax; i++ )
		mpParticles[i].update( cameraPosition, deltaTime );

	sort();
}

void Emitter::draw()
{
	/*for( int i=0; i<mMax; i++ )
		mpParticles[i].draw( mpCamera, mpBillboardProgram );*/

	for( int i=0; i<mAlive; i++ )
		mpSorted[i]->draw( mpCamera, mpBillboardProgram );
}

void Emitter::setPosition( glm::vec3 position )
{
	mPosition = position;
}

glm::vec3 Emitter::getPosition() const
{
	return mPosition;
}

void Emitter::sort()
{
	glm::vec3 cameraPos = mpCamera->getPosition();

	// start by removing any dead particles
	for( int i=0; i<mAlive; i++ )
	{
		glm::vec3 pos = mpSorted[i]->getPosition();
		glm::vec3 dif = cameraPos - pos;

		// The distance is calculated by the square root of the product of all the components
		// of a vector. But the square root operation is really expensive.
		// If we neglect the square on all calculations, we save time without
		// changing the relative values.
		mDistances[i] = dif.x*dif.x + dif.y*dif.y + dif.z*dif.z;

		if( mpSorted[i]->getElapsed() >= mpSorted[i]->getLifetime() )
		{
			mpSorted[i] = mpSorted[--mAlive];
			i--;
		}
	}

	for( int i=0; i<mAlive; i++ )
	{
		bool swapped = false;
		for( int j=0; j<mAlive-i-1; j++ )
		{
			if( mDistances[j] < mDistances[j+1] )
			{
				Particle* temp = mpSorted[j];
				mpSorted[j] = mpSorted[j+1];
				mpSorted[j+1] = temp;

				float t = mDistances[j];
				mDistances[j] = mDistances[j+1];
				mDistances[j+1] = t;

				swapped = true;
			}
		}

		if( !swapped )
			break;
	}
}

Emitter& Emitter::operator=( const Emitter& ref )
{
	if( mpParticles )
		delete[] mpParticles;

	mMax = ref.mMax;
	mpParticles = new Particle[mMax];
	for( int i=0; i<mMax; i++ )
		mpParticles[i] = ref.mpParticles[i];

	mAlive = ref.mAlive;
	for( int i=0; i<mAlive; i++ )
		mpSorted[i] = ref.mpSorted[i];

	return *this;
}

Emitter::Emitter( const Emitter& ref )
	: mMax( ref.mMax ), mAlive( ref.mAlive )
{
	mpParticles = new Particle[mMax];
	for( int i=0; i<mMax; i++ )
		mpParticles[i] = ref.mpParticles[i];
	for( int i=0; i<mAlive; i++ )
		mpSorted[i] = ref.mpSorted[i];
}

Emitter::Emitter( int maxParticles )
	: mMax( maxParticles ), mpParticles( nullptr ), mPosition( 0.0f, 0.0f, 0.0f ), mAlive( 0 )
{
}

Emitter::~Emitter()
{
	if( mpParticles )
	{
		delete[] mpParticles;
		delete[] mpSorted;
	}
}