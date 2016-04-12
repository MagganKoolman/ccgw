#pragma once

#include <vector>
#include "FbxMesh.h"
#include "FbxLight.h"
#include "FbxCamera.h"
#include <assert.h>
#include <iostream>
#include <string>
#include "fbxsdk.h"

using namespace std;

class FbxImport
{
public:
	/*Functions*/

	void initializeImporter();
	void processMesh(FbxMesh* inputMesh);

	void processVertices(FbxMesh* inputMesh);
	void processNormals(FbxMesh* inputMesh);
	void processTangents(FbxMesh* inputMesh);
	void processBiTangents(FbxMesh* inputMesh);
	void processUVs(FbxMesh* inputMesh);
	void processMaterials(FbxMesh* inputMesh);

	void processTextures(FbxMesh* inputMesh);
	void processDiffuseMaps(FbxProperty inputProp);
	void processSpecularMaps(FbxProperty inputProp);
	void processNormalMaps(FbxProperty inputProp);


	void processTransformations(FbxMesh* inputMesh);

	void processLight(FbxLight* inputLight);
	void processCamera(FbxCamera* inputCamera);

	std::vector<MeshFbx> mMeshList;
	//for(mMeshList.size()):
	//vertices localVertexList = mMeshList[i].getVertices();
	//material currMat = mMeshList[i].getMaterial();
	//matrix meshOis = 
	std::vector<LightFbx*> mLightList;
	std::vector<CameraFbx*> mCameraList;

	MeshFbx mesh;
	CameraFbx camera;

	FbxImport();
	~FbxImport();

private:

	FbxNode* pmRootNode;
	FbxManager* pmManager;
	FbxIOSettings* pmSettings;
	FbxScene* pmScene;

	int meshCounter;
	int materialCounter;
	int textureCounter;
	int cameraCounter;
	int lightCounter;
};



