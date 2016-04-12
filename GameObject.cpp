#include "GameObject.h"

void GameObject::update() {

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
	:mLookat(0,0,1), mWorld(0.0f), mRotation(0.0f, 0.0f, 0.0f, 0.0f), mpMesh(nullptr), mpTexture(nullptr)
{
	mPosition = { 0, 0, -3 };
	mWorld = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
}

GameObject::~GameObject()
{
}