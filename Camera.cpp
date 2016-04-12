#include "Camera.h"

#include "glm\gtx\transform.hpp"
#include "glm\gtc\matrix_transform.hpp"

void Camera::follow( glm::vec3 position, const glm::vec3 &lookDir, float distance )
{
	mPosition = position + ( -lookDir * distance );
	mView = glm::lookAt(mPosition, mPosition + lookDir, glm::vec3(0, 1, 0));
}

void Camera::update(const GLuint &programID) {
	glm::mat4 viewPersp = mPerspective * mView;
	GLuint viewPerspective = glGetUniformLocation(programID, "viewProjection");
	glUniformMatrix4fv(viewPerspective, 1, GL_FALSE, &viewPersp[0][0]);
}

void Camera::setPerspective( float fov, float aspectRatio, float nearplane, float farplane )
{
	mPerspective = glm::perspective( fov, aspectRatio, nearplane, farplane );
}

void Camera::setPosition( glm::vec3 position )
{
	mPosition = position;
	mView = glm::translate( glm::mat4(), -position );
}

glm::vec3 Camera::getPosition() const
{
	return mPosition;
}

const glm::mat4& Camera::getView() const
{
	return mView;
}

const glm::mat4& Camera::getPerspective() const
{
	return mPerspective;
}

glm::mat4 Camera::getViewPerspective() const
{
	return mView * mPerspective;
}

Camera& Camera::operator=( const Camera& ref )
{
	mPosition = ref.mPosition;
	mView = ref.mView;
	mPerspective = ref.mPerspective;
	return *this;
}

Camera::Camera( const Camera& ref )
	: mPosition( ref.mPosition ), mView( ref.mView ), mPerspective( ref.mPerspective )
{
}

Camera::Camera( float fov, float aspectRatio, float nearplane, float farplane )
{
	setPerspective( fov, aspectRatio, nearplane, farplane );
	//mView = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 5) + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
}

Camera::~Camera()
{
}