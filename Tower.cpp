#include "Tower.h"

Tower::Tower(glm::vec3 position, const Tower &towerRef, float scale): GameObject(position, scale)
{
	this->mpMesh = towerRef.mpMesh;
	this->mpTexture = towerRef.mpTexture;
	this->mpSpecularMap = towerRef.mpSpecularMap;
	this->mpNormalMap = towerRef.mpNormalMap;
}

Tower::Tower()
{
	
}


Tower::~Tower()
{
}
