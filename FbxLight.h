#pragma once

#include <vector>
#include "fbxsdk.h"

class LightFbx 
{
public:

	struct sLight
	{
		float color[3];
		float intensity; 

		float lightPos[3];
		float lightRot[3];
		float lightScale[3];
	};

	sLight lightData;

	std::vector<sLight>mLightList;

	LightFbx();
	~LightFbx();
private:
	
};
