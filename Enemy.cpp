#include "Enemy.h"

void Enemy::update()
{
	if( mCurrent >= 0 )
	{
		glm::vec3 target( pPath[mCurrent].x, 0, pPath[mCurrent].y );

		float dist = glm::distance( mPosition, glm::vec3( target ) );
		if( dist < 0.01f )
		{
			mCurrent--;
			mPosition = target;
		}
		else
		{
			glm::vec3 dir = glm::normalize( target - mPosition );
			mPosition += dir * 0.01f;
		}

		mWorld[3][0] = mPosition.x;
		mWorld[3][1] = mPosition.y;
		mWorld[3][2] = mPosition.z;
	}
}

void Enemy::render( GLuint programID )
{
	GameObject::render( programID );

	GLuint worldLocation = glGetUniformLocation( programID, "world" );
	for( int i=0; i<mCurrent; i++ )
	{
		glm::mat4 world;
		world[3][0] = pPath[i].x;
		world[3][1] = 0.1f;
		world[3][2] = pPath[i].y;

		glUniformMatrix4fv( worldLocation, 1, GL_FALSE, &world[0][0] );

		mpMesh->draw();
	}
}

void Enemy::setPath( sNode* path, int max )
{
	pPath = path;
	mCurrent = max-1;
}

Enemy& Enemy::operator=( const Enemy& ref )
{
	GameObject::operator=( ref );
	mCurrent = ref.mCurrent;
	pPath = ref.pPath;
	return *this;
}

Enemy::Enemy( const Enemy& ref )
	: GameObject( ref ), mCurrent( ref.mCurrent ), pPath( ref.pPath )
{
}

Enemy::Enemy( glm::vec3 position )
	: GameObject( position, 1.0f ), mCurrent( 0 ), pPath( nullptr )
{
	this->mBoundRadius = 1.0f;
}

Enemy::Enemy()
	: mCurrent( 0 ), pPath( nullptr )
{
	this->mBoundRadius = 1.0f;
}

Enemy::~Enemy()
{
}