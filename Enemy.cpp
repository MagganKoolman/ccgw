#include "Enemy.h"

void Enemy::render( GLuint programID )
{
	GameObject::render( programID );

	// change to 1 to draw the path
#if 0
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
#endif
}

void Enemy::setPath( sNode* path, int max )
{
	pPath = path;
	mCurrent = max-1;
}

void Enemy::imHit(float strength)
{
	mLife -= strength;
	if (mLife <= 0) {
		mAlive = false;
	}
}

void Enemy::setAlive( bool alive )
{
	mAlive = alive;
}

void Enemy::setLife( float life )
{
	mLife = life;
}

bool Enemy::getAlive() const
{
	return mAlive;
}

float Enemy::getLife() const
{
	return mLife;
}

const BoundingBox& Enemy::getBoundingBox() const
{
	return mBoundingBox;
}

const BoundingBox& Enemy::getHeadBox() const
{
	return mHeadBox;
}

Enemy& Enemy::operator=( const Enemy& ref )
{
	GameObject::operator=( ref );
	mCurrent = ref.mCurrent;
	pPath = ref.pPath;
	mAlive = ref.mAlive;
	return *this;
}

Enemy::Enemy( const Enemy& ref )
	: GameObject( ref ), mCurrent( ref.mCurrent ), pPath( ref.pPath ), mAlive( ref.mAlive ), mBoundingBox( ref.mBoundingBox )
{
}

Enemy::Enemy( glm::vec3 position )
	: GameObject( position, 1.0f ), mCurrent( -1 ), pPath( nullptr ), mAlive( false ), mLife(1), mBoundingBox( position, 0.5f )
{
	this->mBoundRadius = 1.0f;
}

Enemy::Enemy()
	: mCurrent(-1), pPath(nullptr), mAlive(false), mLife(1), mBoundingBox( glm::vec3( 0.0f ), 0.5f )
{
	this->mBoundRadius = 1.0f;
}

Enemy::~Enemy()
{
}