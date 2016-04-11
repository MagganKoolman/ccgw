#include "Camera.h"
#include <gl\glew.h>
#include "glm\gtx\transform.hpp"
#include "glm\gtc\matrix_transform.hpp"

/*bool Camera::update() {
	return true;
}

glm::mat4x4* Camera::getViewMat() const {
	return mViewMat;
}

glm::mat4x4* Camera::getPerspectiveMat() const {
	return mPerspectiveMat;
}

Camera::Camera()
{
	mPosition = glm::vec3(0, 0, -5);
	mViewDir = glm::vec3(0, 0, 1);
	mPerspectiveMat = &glm::perspective(45.0f, 1080.f / 720.0f, 0.5f, 75.0f);
	mViewMat = &glm::lookAt(mPosition, mPosition + mViewDir, glm::vec3(0, 1, 0));
}

Camera::~Camera()
{
}*/

void Camera::follow( glm::vec3 position, float rotation, float distance )
{
	glm::vec3 dir( cos( rotation ), 0.0f, sin( rotation ) );
	dir = -normalize( dir );
	mPosition = position + ( dir * distance );
}

void Camera::setPerspective( float fov, float aspectRatio, float nearplane, float farplane )
{
	mPerspective = glm::perspective( fov, aspectRatio, nearplane, farplane );
}

void Camera::setPosition( glm::vec3 position )
{
	mPosition = position;
	mView = glm::translate( glm::mat4(), position );
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
}

Camera::~Camera()
{
}