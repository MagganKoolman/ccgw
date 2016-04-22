#pragma once

#include "GameObject.h"
#include "Grid.h"
#include <iostream>

class Enemy : public GameObject
{
public:
	void update();
	void render( GLuint programID );

	void setPath( sNode* path, int max );

	Enemy& operator=( const Enemy& ref );
	Enemy( const Enemy& ref );
	Enemy( glm::vec3 position );
	Enemy();
	~Enemy();

private:
	sNode* pPath;
	int mCurrent;
};