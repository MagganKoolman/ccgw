#include "Camera.h"
#include <iostream>

#include "glm\gtx\transform.hpp"
#include "glm\gtc\matrix_transform.hpp"

void Camera::follow( glm::vec3 position, const glm::vec3 &lookDir, float distance )
{
	mPosition = position - distance * lookDir + glm::vec3(glm::cross(lookDir, glm::cross(glm::vec3(0,1,0),lookDir)))*(distance/4);// (-lookDir * distance);
	mView = glm::lookAt(mPosition, position + lookDir*distance, glm::vec3(0, 1, 0));
}

/*void Camera::update(const GLuint &programID) {
	glm::mat4 viewPersp = mPerspective * mView;
	GLuint viewPerspective = glGetUniformLocation(programID, "viewProjection");
	glUniformMatrix4fv(viewPerspective, 1, GL_FALSE, &viewPersp[0][0]);

	GLuint cameraPos = glGetUniformLocation(programID, "cameraPos");
	glUniform3fv(cameraPos, 1, &mPosition[0]);
}*/

void Camera::updateUniforms( GLuint viewPerspective, GLuint cameraPosition )
{
	glUniformMatrix4fv(viewPerspective, 1, GL_FALSE, &getViewPerspective()[0][0] );
	glUniform3fv( cameraPosition, 1, &mPosition[0] );
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
	return mPerspective * mView;
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