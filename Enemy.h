#pragma once

#include "GameObject.h"
#include "Grid.h"

class Enemy : public GameObject
{
public:
	void update();

	void setPath( sNode* path, int max );

	Enemy& operator=( const Enemy& ref );
	Enemy( const Enemy& ref );
	Enemy( glm::vec3 position );
	Enemy();
	~Enemy();

private:
	sNode* pPath;
	int mMax, mCurrent;
};