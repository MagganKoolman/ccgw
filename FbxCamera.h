#pragma once

#include <vector>
#include "fbxsdk.h"

class CameraFbx
{
public:

	struct sCamData
	{
		float camPos[3];
		float upVector[3];

		float fov;
		float nearPlane;
		float farPlane;
	};

	sCamData camData;

	std::vector<sCamData> mpCameraList;

	CameraFbx();
	~CameraFbx();

private:
	
};