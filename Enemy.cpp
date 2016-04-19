#include "Enemy.h"

void Enemy::update()
{
	if( mCurrent < mMax )
	{
		glm::vec3 target( pPath[mCurrent].x, 0, pPath[mCurrent].y );

		float dist = glm::distance( mPosition, glm::vec3( target ) );
		if( dist < 0.5f )
		{
			mCurrent++;
		}
		else
		{
			glm::vec3 dir = glm::normalize( target - mPosition );
			mPosition += dir * 0.01f;
			mWorld[3][0] = mPosition.x;
			mWorld[3][1] = mPosition.y;
			mWorld[3][2] = mPosition.z;
		}
	}
}

void Enemy::setPath( sNode* path, int max )
{
	pPath = path;
	mMax = max;
	mCurrent = 0;
}

Enemy& Enemy::operator=( const Enemy& ref )
{
	GameObject::operator=( ref );
	mMax = ref.mMax;
	mCurrent = ref.mCurrent;
	pPath = ref.pPath;
	return *this;
}

Enemy::Enemy( const Enemy& ref )
	: GameObject( ref ), mMax( ref.mMax ), mCurrent( ref.mCurrent ), pPath( ref.pPath )
{
}

Enemy::Enemy( glm::vec3 position )
	: GameObject( position ), mMax( 0 ), mCurrent( 0 ), pPath( nullptr )
{
}

Enemy::Enemy()
	: mMax( 0 ), mCurrent( 0 ), pPath( nullptr )
{
}

Enemy::~Enemy()
{
}