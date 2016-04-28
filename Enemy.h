#pragma once

#include "GameObject.h"
#include "Grid.h"
#include "glm\gtx\vector_angle.hpp"

//Abstract class for enemies.
class Enemy : public GameObject
{
public:
	//Render the enemy.
	void render( GLuint programID );

	//Set the path that this enemy should follow.
	void setPath( sNode* path, int max );

	void setAlive( bool alive );
	bool getAlive() const;

	Enemy& operator=( const Enemy& ref );
	Enemy( const Enemy& ref );
	Enemy( glm::vec3 position );
	Enemy();
	~Enemy();

protected:
	float mBoundRadius;
	sNode* pPath;
	int mCurrent;
	bool mAlive;
};