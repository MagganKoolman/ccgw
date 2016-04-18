#include "GameObject.h"
#include <iostream>

bool GameObject::load(tempMesh* assets, Texture* diffuseTex, Texture* specularMap, Texture* normalMap)
{
	if (assets != nullptr)
		mpMesh = assets;
	if (diffuseTex != nullptr)
		mpTexture = diffuseTex;
	if (specularMap != nullptr)
		mpSpecularMap = specularMap;
	if (normalMap != nullptr)
		mpNormalMap= normalMap;

	return (mpMesh != nullptr);
}

bool GameObject::loadTex(Texture* texture) {
	mpTexture = texture;
	return (mpTexture != nullptr);
}

void GameObject::update(const float &dt) {
}

void GameObject::render(const GLuint & programID)
{
	GLuint world = glGetUniformLocation(programID, "world");
	glUniformMatrix4fv(world, 1, GL_FALSE, &this->mWorld[0][0]);

	activateTextures(programID);
	mpMesh->draw();
	deactivateTextures();
}

void GameObject::render(const GLuint & programID, const glm::mat4 &viewMat)
{
	GLuint world = glGetUniformLocation(programID, "world");
	glUniformMatrix4fv(world, 1, GL_FALSE, &this->mWorld[0][0]);

	activateTextures(programID);
	mpMesh->draw();
	deactivateTextures();
}

void GameObject::activateTextures(const GLuint &programID) {
	GLuint texLocation = glGetUniformLocation(programID, "texSampler");
	glUniform1i(texLocation, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mpTexture->getID());
	if (mpSpecularMap != nullptr) {
		GLuint specularLocation = glGetUniformLocation(programID, "specularSampler");
		glUniform1i(specularLocation, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, mpSpecularMap->getID());
	}
	if (mpNormalMap != nullptr) {
		GLuint normalLocation = glGetUniformLocation(programID, "normalSampler");
		glUniform1i(normalLocation, 2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, mpNormalMap->getID());
	}
}

void GameObject::deactivateTextures() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
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
	: mRotation(0.0f, 0.0f, 0.0f, 0.0f), mpMesh(nullptr), mpTexture(nullptr), mpSpecularMap(nullptr), mpNormalMap(nullptr)
{
	mPosition = { 0, 0, 0 };
	mLookat = { 0, 0, -1 };
	mWorld = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
}

GameObject::~GameObject()
{

}