#include "Moleratman.h"

void Moleratman::update()
{
	if (mCurrent >= 0)
	{
		glm::vec3 target(pPath[mCurrent].x, 0, pPath[mCurrent].y);

		float dist = glm::distance(mPosition, glm::vec3(target));
		if (dist < MOLERATMAN_SPEED)
		{
			mCurrent--;
			mPosition = target;
		}
		else
		{
			glm::vec3 dir = glm::normalize(target - mPosition);
			mPosition += dir * MOLERATMAN_SPEED;
		}

		mWorld[3][0] = mPosition.x;
		mWorld[3][1] = mPosition.y;
		mWorld[3][2] = mPosition.z;

		// face the direction of movement
		glm::vec3 dir = glm::normalize( target - mPosition );

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