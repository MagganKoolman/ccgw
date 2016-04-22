#include "Molebat.h"

void Molebat::update()
{
	glm::vec3 newPos = mPosition;
	glm::vec3 movement;

	// chase the player
	glm::vec3 dir = pGameData->pPlayer->getPosition() - mPosition;
	float dist = glm::length( dir );
	if( dist > MOLEBAT_FAR_DISTANCE )
	{
		dir = glm::normalize( dir );
		movement += dir;
	}
	else if( dist < MOLEBAT_NEAR_DISTANCE )
	{
		dir = -glm::normalize( dir );
		movement += dir;
	}

	newPos += movement * 0.1f;

	// stay above ground
	if( newPos.y < MOLEBAT_HEIGHT )
		newPos.y = MOLEBAT_HEIGHT;

	// evade other molebats
	glm::vec3 evade;
	for( int i=0; i<pGameData->mMolebats; i++ )
	{
		if( &pGameData->pMolebats[i] == this )
			continue;

		glm::vec3 dir = pGameData->pMolebats[i].getPosition() - newPos;
		float dist = glm::length( dir );
		if( dist < MOLEBAT_ALLY_DISTANCE )
		{
			dir = -glm::normalize( dir );
			dist = MOLEBAT_ALLY_DISTANCE - dist;
			evade += dir * dist;
		}
	}

	newPos += evade;

	// face the direction of flight
	mLookat = glm::normalize( glm::vec3( dir.x, 0.0f, dir.z ) );
	float rotY = -glm::angle( mLookat, glm::vec3( 1.0f, 0.0f, 0.0f ) );
	if( mLookat.z < 0.0f )
		rotY *= -1.0f;

	// set data for rendering
	mPosition = newPos;
	mWorld = {
		cosf( rotY ),	0,		-sinf( rotY ),	0,
		0,				1,		0,				0,
		sinf(rotY),		0,		cosf(rotY),		0,
		mPosition.x,	mPosition.y,	mPosition.z, 1
	};
}

Molebat& Molebat::operator=( const Molebat& ref )
{
	Enemy::operator=( ref );
	mSin = ref.mSin;
	return *this;
}

Molebat::Molebat( const Molebat& ref )
	: Enemy( ref ), pGameData( ref.pGameData ), mSin( ref.mSin )
{
}

Molebat::Molebat( GameData* data, glm::vec3 position )
	: Enemy( position ), pGameData( data ), mSin( rand() % 1000 )
{
}

Molebat::~Molebat()
{
}