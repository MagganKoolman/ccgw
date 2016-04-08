#pragma once

#include <GLM\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include "Mesh.h"
#include "Texture.h"
#include "Input.h"

class GameObject
{
public:
	/*Abstract method. Don't call.*/
	virtual bool load(Assets* assets) = 0;
	/*Abstract method. Don't call.*/
	virtual void update(Input* input) = 0;
	/*Abstract method. Don't call.*/
	virtual void render(GLuint programID);

	GameObject(const GameObject& ref);
	GameObject();
	virtual ~GameObject();

protected: // <-- changed to protected from private. because i wanted to reach these from subclasses.
	glm::vec3 mPosition;
	glm::quat mRotation;

	Mesh* mpMesh;
	Texture* mpTexture;
};