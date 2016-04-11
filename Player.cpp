#include "Player.h"

bool Player::load(tempMesh* assets) 
{
	mpMesh = assets;
	return (mpMesh != nullptr);
}

void Player::render(const GLuint &programID)
{
	GLuint world = glGetUniformLocation(programID, "world");
	glUniformMatrix4fv(world, 1, GL_FALSE, &this->mWorld[0][0]);
	mpMesh->draw();
}

void Player::update(Input* inputs)
{
	
}

Player::Player() : GameObject() 
{
	mWorld = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
}

Player::~Player()
{

}