#include "Terrain.h"

bool Terrain::load(tempMesh * assets)
{
	mpMesh = assets;
	return (mpMesh != nullptr);
}

void Terrain::render(const GLuint & programID)
{
	GLuint world = glGetUniformLocation(programID, "world");
	glUniformMatrix4fv(world, 1, GL_FALSE, &this->mWorld[0][0]);
	mpMesh->draw();
}

Terrain::Terrain() : GameObject() {

}

Terrain::~Terrain() {

}