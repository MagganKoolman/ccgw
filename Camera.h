#pragma once

#include <vector>
#include <glm\glm.hpp>
#include "GameObject.h"
//#include "fbxsdk.h"

class Camera
{
public:
	bool update();
	glm::mat4x4* getViewMat() const;
	glm::mat4x4* getPerspectiveMat() const;

	Camera();
	~Camera();
private:
	glm::vec3 mPosition;
	glm::vec3 mViewDir;
	glm::mat4x4* mViewMat;
	glm::mat4x4* mPerspectiveMat;

	void passUniforms();
	void follow(GameObject* object);
};