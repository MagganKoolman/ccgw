#pragma once
#include <vector>

struct read_sMainHeader
{
	unsigned int meshCount;
	unsigned int materialCount;
	unsigned int lightCount;
	unsigned int cameraCount;
};

struct  read_sVertex
{
	float vertexPos[3];
	float vertexNormal[3];
	float vertexUV[2];
	float tangentNormal[3];
	float biTangentNormal[3];
};

struct  read_sMesh
{
	unsigned int materialID;

	float translate[3];
	float rotation[3];
	float scale[3];

	unsigned int vertexCount;
	//unsigned int skelAnimVertexCount;
	//unsigned int jointCount;

};

static std::vector< read_sMesh>  read_meshList;


struct  read_m
{
std::vector< read_sVertex> vList;
};

static std::vector< read_m>  read_mList;



struct  read_sSkelAnimVertex
{
	float vertexPos[3];
	float vertexNormal[3];
	float vertexUV[2];
	float tangentNormal[3];
	float biTangentNormal[3];
	float influences[4];
	float weights[4];
};

struct  read_sMaterial
{
	const char* materialName;

	float ambientColor[3];
	float diffuseColor[3];
	float specularColor[3];

	float shinyFactor;

	wchar_t* diffuseTexture;
	wchar_t* specularTexture;
	wchar_t* normalTexture;
};

static std::vector< read_sMaterial>  read_materialList;

struct  read_sLight
{
	unsigned int directionalPointCount;
	unsigned int spotlightCount;
};


struct  read_sDirectionalPoint
{
	float lightPos[3];
	float lightRot[3];
	float lightScale[3];

	float color[3];
	float intensity;
};

struct  read_sSpotLight
{
	float lightPos[3];
	float lightRot[3];
	float lightScale[3];

	float color[3];
	float intensity;

	float innerAngle;
	float outerAngle;
};

static std::vector< read_sDirectionalPoint>  read_mDirPointList;
static std::vector< read_sSpotLight>  read_mSpotList;

struct  read_sCamera
{
	float camPos[3];
	float upVector[3];

	float fieldOfView;
	float nearPlane;
	float farPlane;
};

static std::vector<read_sCamera>  read_mCameraList;

//Struct objects

read_sMainHeader read_mainHeader;
read_sVertex read_vertex;
read_sMaterial read_materialData;
read_sLight read_lightData;
read_sDirectionalPoint read_dirPointData;
read_sSpotLight read_spotData;
read_sCamera read_camData;

