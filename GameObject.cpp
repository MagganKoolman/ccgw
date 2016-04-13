#include "GameObject.h"

bool GameObject::load(tempMesh* assets)
{
	mpMesh = assets;
	return (mpMesh != nullptr);
}

bool GameObject::loadTex(Texture * texture)
{
	mpTexture = texture;
	return (mpTexture != nullptr);
}

void GameObject::update(const float &dt) {
}

void GameObject::render(const GLuint & programID)
{
	GLuint world = glGetUniformLocation(programID, "world");
	glUniformMatrix4fv(world, 1, GL_FALSE, &this->mWorld[0][0]);
	GLuint texLocation = glGetUniformLocation(programID, "texSampler");
	glUniform1i(texLocation, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mpTexture->getID());
	mpMesh->draw();
}

glm::vec3 GameObject::getPosition() const
{
	return mPosition;
}

GameObject::GameObject(const GameObject& ref)
	: mWorld(ref.mWorld), mRotation(ref.mRotation), mpMesh(ref.mpMesh), mpTexture(ref.mpTexture)
{

}

GameObject::GameObject(glm::vec3 position = { 0, 0, 0 })
{
	mPosition = position;
}

GameObject::GameObject()
	: mRotation(0.0f, 0.0f, 0.0f, 0.0f), mpMesh(nullptr), mpTexture(nullptr)
{
	mPosition = { 0, 0, 0 };
	mLookat = { 0, 0, -1 };
	mWorld = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
}

GameObject::~GameObject()
{

}