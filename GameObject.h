#pragma once

#include <GLM\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include "tempMesh.h"
#include "Texture.h"
#include "Input.h"

class GameObject
{
public:
	/*Abstract method. Don't call.*/
	virtual bool load(tempMesh* assets) = 0;
	/*Abstract method. Don't call.*/
	virtual void update();
	/*Abstract method. Don't call.*/
	virtual void render(const GLuint &programID) = 0;

	GameObject(const GameObject& ref);
	GameObject();
	virtual ~GameObject();
protected: // <-- changed to protected from private. because i wanted to reach these from subclasses.
	glm::mat4 mWorld;
	glm::quat mRotation;
	glm::vec3 mLookat;
	glm::vec3 mPosition;

	tempMesh* mpMesh;
	Texture* mpTexture;
};