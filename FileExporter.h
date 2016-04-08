#pragma once
#include "FbxImport.h"

class FileExporter {

public:

	struct sMesh
	{
		unsigned int vertexCount;
		unsigned int transformCount;
	};

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

		float shinyFactor;

		char* diffuseTexture;
		char* specularTexture;
		char* normalTexture;
	};

	

	FileExporter();
	~FileExporter();
private:


};