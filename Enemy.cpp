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

void Enemy::setAlive( bool alive )
{
	mAlive = alive;
}

bool Enemy::getAlive() const
{
	return mAlive;
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
	: GameObject( ref ), mCurrent( ref.mCurrent ), pPath( ref.pPath ), mAlive( ref.mAlive )
{
}

Enemy::Enemy( glm::vec3 position )
	: GameObject( position, 1.0f ), mCurrent( -1 ), pPath( nullptr ), mAlive( false )
{
	this->mBoundRadius = 1.0f;
}

Enemy::Enemy()
	: mCurrent( -1 ), pPath( nullptr ), mAlive( false )
{
	this->mBoundRadius = 1.0f;
}

Enemy::~Enemy()
{
}