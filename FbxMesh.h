#pragma once

#include <vector>
#include "fbxsdk.h"

class Mesh
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
		FbxAMatrix worldPos;
		FbxAMatrix worldRot;
		FbxAMatrix worldScale; 
	};

	struct sMaterialData
	{
		float ambientColor[3];
		float diffuseColor[3];
		float specularColor[3];

		char* diffuseTexture;
		char* specularTexture;
		char* normalTexture;
	};

	sVertexData vertexData;
	sMaterialData materialData;

	std::vector<sVertexData> mpVertexList;
	std::vector<sMaterialData> mpMaterialList;

	Mesh();
	~Mesh();

private:
};

