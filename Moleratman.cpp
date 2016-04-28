#include "Moleratman.h"

void Moleratman::update()
{
	Enemy::update();

	if( mCurrent >= 0 )
	{
		sNode target = pPath[mCurrent];
		glm::vec3 pos( target.x, 0.5f, target.y );
		glm::vec3 dir = glm::normalize( pos - mPosition );

		mLookat = glm::normalize(glm::vec3(dir.x, 0.0f, dir.z));
		float rotY = -glm::angle(mLookat, glm::vec3(1.0f, 0.0f, 0.0f));
		if (mLookat.z < 0.0f)
			rotY *= -1.0f;

		mWorld = {
			cosf(rotY),	0,		-sinf(rotY),	0,
			0,				1,		0,				0,
			sinf(rotY),		0,		cosf(rotY),		0,
			mPosition.x,	mPosition.y,	mPosition.z, 1
		};
	}
}

Moleratman& Moleratman::operator=( const Moleratman& ref )
{
	Enemy::operator=( ref );
	return *this;
}

Moleratman::Moleratman( const Moleratman& ref )
	: Enemy( ref )
{
}

Moleratman::Moleratman()
{
}

Moleratman::~Moleratman()
{
}