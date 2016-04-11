#pragma once

#include <vector>
#include <glm\glm.hpp>
#include "fbxsdk.h"

/*class Camera
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
};*/

class Camera
{
public:
	/*Makes the camera follow a target offset by the supplied distance.*/
	void follow( glm::vec3 position, float rotation, float distance );

	// Getters & Setters are evul!

	void setPerspective( float fov, float aspectRatio, float nearplane = 0.01f, float farplane = 100.0f );
	void setPosition( glm::vec3 position );
	glm::vec3 getPosition() const;
	const glm::mat4& getView() const;
	const glm::mat4& getPerspective() const;
	glm::mat4 getViewPerspective() const;

	Camera& operator=( const Camera& ref );
	Camera( const Camera& ref );
	Camera( float fov, float aspectRatio, float nearplane = 0.01f, float farplane = 100.0f );
	~Camera();

private:
	glm::vec3 mPosition;
	glm::mat4 mView;
	glm::mat4 mPerspective;
};