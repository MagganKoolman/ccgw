#include "GameObject.h"

void GameObject::render(GLuint programID) {
	GLuint location = glGetUniformLocation(programID, "texture");
	//glUniform1i(location, this->mpTexture->getID()); // need to get the GLunit of texture somehow
	
	//glDrawArrays(GL_TRIANGLES, startVariable, startVariable + sizeVariable);
}

GameObject::GameObject(const GameObject& ref)
	: mPosition(ref.mPosition), mRotation(ref.mRotation), mpMesh(ref.mpMesh), mpTexture(ref.mpTexture)
{
}

GameObject::GameObject()
	: mPosition(0.0f), mRotation(0.0f, 0.0f, 0.0f, 0.0f), mpMesh(nullptr), mpTexture(nullptr)
{
}

GameObject::~GameObject()
{
}