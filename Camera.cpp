#include "Camera.h"
#include <gl\glew.h>
#include "glm\gtx\transform.hpp"
#include "glm\gtc\matrix_transform.hpp"

bool Camera::update() 
{
	return true;
}

glm::mat4x4* Camera::getViewMat() const 
{
	return mViewMat;
}

glm::mat4x4* Camera::getPerspectiveMat() const 
{
	return mPerspectiveMat;
}

Camera::Camera()
{
	mPosition = glm::vec3(0, 0, -5);
	mViewDir = glm::vec3(0, 0, 1);
	mPerspectiveMat = new glm::mat4x4(glm::perspective(45.0f, 1080.f / 720.0f, 0.5f, 75.0f));
	mViewMat = new glm::mat4x4(glm::lookAt(mPosition, mPosition + mViewDir, glm::vec3(0, 1, 0))); 
}

Camera::~Camera()
{
}

