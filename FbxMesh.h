#pragma once

#include <vector>
#include "fbxsdk.h"

class MeshFbx
{
public:

	struct sVertexData
	{
		float vertexPos[3];
		float vertexNormal[3];
		float tangentNormal[3];
		float biTangentNormal[3];
		float vertexUV[2];
	};

	struct sTransformData
	{
		float transformData[4][4];
	};

	struct sMaterialData
	{
		float ambientColor[3];
		float diffuseColor[3];
		float specularColor[3];

		float shinyFactor;

		wchar_t* diffuseTexture;
		wchar_t* specularTexture;
		wchar_t* normalTexture;
	};

	sVertexData vertexData;
	sMaterialData materialData;

	std::vector<sVertexData> mpVertexList;
	std::vector<sTransformData> mpTransformList;
	std::vector<sMaterialData> mpMaterialList;

	MeshFbx();
	~MeshFbx();

private:
};


