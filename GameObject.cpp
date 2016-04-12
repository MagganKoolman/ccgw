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
	: mRotation(0.0f, 0.0f, 0.0f, 0.0f), mpMesh(nullptr), mpTexture(nullptr)
{
	mPosition = { 0, 0, 0 };
	mWorld = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
}

GameObject::~GameObject()
{

}