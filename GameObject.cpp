#include "GameObject.h"

void GameObject::update() {

}

GameObject::GameObject(const GameObject& ref)
	: mWorld(ref.mWorld), mRotation(ref.mRotation), mpMesh(ref.mpMesh), mpTexture(ref.mpTexture)
{

}

GameObject::GameObject()
	:mLookat(0,0,1), mWorld(0.0f), mRotation(0.0f, 0.0f, 0.0f, 0.0f), mpMesh(nullptr), mpTexture(nullptr)
{
}

GameObject::~GameObject()
{
}