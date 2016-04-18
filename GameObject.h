#pragma once

#include <GLM\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "tempMesh.h"
#include "Texture.h"
#include "Input.h"
#include "GameData.h"

class GameObject
{
public:
	/*Abstract method. Don't call.*/
	bool load(tempMesh* assets);
	bool loadTex(Texture* texture);
	/*Abstract method. Don't call.*/
	virtual void update(const float &dt);
	/*Abstract method. Don't call.*/
	virtual void render(const GLuint &programID);
	virtual void render(const GLuint &programID, const glm::mat4 &viewMat);
	glm::vec3 getPosition() const;

	GameObject(const GameObject& ref);
	GameObject(glm::vec3 position);
	GameObject();
	virtual ~GameObject();
protected: // <-- changed to protected from private. because i wanted to reach these from subclasses.
	glm::mat4 mWorld;
	glm::vec3 mPosition;
	glm::vec3 mLookat;
	glm::quat mRotation;

	tempMesh* mpMesh;
	Texture* mpTexture;
};