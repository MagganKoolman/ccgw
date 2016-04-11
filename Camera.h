#pragma once

#include <vector>
#include <glm\glm.hpp>
#include "fbxsdk.h"

class Camera
{
public:
	Camera();
	~Camera();
	bool update();
	glm::mat4x4* getViewMat() const;
	glm::mat4x4* getPerspectiveMat() const;
private:
	glm::vec3 mPosition;
	glm::vec3 mViewDir;
	glm::mat4x4* mViewMat;
	glm::mat4x4* mPerspectiveMat;

	void passUniforms();
};