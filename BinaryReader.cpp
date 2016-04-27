
#include <GL\glew.h>
#include <fstream>
#include <vector>
#include <iostream>
#include "ReadHeaderData.h"
#include "BinaryReader.h"

using namespace std;

void BinaryReader::readFromBinary(GLuint &vao)
{

	//Read from binary
	std::ifstream infile("testBin.bin", std::ifstream::binary);//		Öppnar filen vi nyss skapade men ska nu läsa istället

	cout << ">>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<" << "\n" << "\n" << endl;
	cout << "Binary Reader" << endl;
	cout << "\n" << endl;

	infile.read((char*)&read_mainHeader, sizeof(read_sMainHeader));//				Information av hur många meshes som senare kommer att komma, och efter det hur många material osv, samt hur mycket minne den inten som berättar detta tar upp (reservation för vår header)
	cout << "______________________" << endl;
	cout << "Main Header" << endl;
	cout << "meshCount: " << read_mainHeader.meshCount << endl;
	cout << "materialCount: " << read_mainHeader.materialCount << endl;
	cout << "lightCount: " << read_mainHeader.lightCount << endl;
	cout << "cameraCount: " << read_mainHeader.cameraCount << endl;

	cout << "______________________" << endl;

	if (read_mainHeader.meshCount >= 1)
	{
		read_meshList.resize(read_mainHeader.meshCount);
		read_mList.resize(read_mainHeader.meshCount);

		for (int i = 0; i < read_mainHeader.meshCount; i++)
		{
			infile.read((char*)&read_meshList[i], sizeof(read_sMesh));

			cout << "Mesh: " << i << endl;

			cout << "Name: " << read_meshList[i].meshName << endl;

			//Information av hur många vertices som senare kommer att komma, och efter det hur många skelAnim verticear som kommer komma osv, samt hur mycket minne den inten som berättar detta tar upp(reservation för vår header).En int kommer först, den har värdet 100.  Och den inten kommer ta upp 4 bytes.

			cout << "Mesh vector: " << endl;

			cout << "\t";
			cout << "xyz: ";
			cout << read_meshList[i].translate[0];
			cout << read_meshList[i].translate[1];
			cout << read_meshList[i].translate[2] << endl;

			cout << "\t";
			cout << "rot: ";
			cout << read_meshList[i].rotation[0];
			cout << read_meshList[i].rotation[1];
			cout << read_meshList[i].rotation[2] << endl;

			cout << "\t";
			cout << "scale: ";
			cout << read_meshList[i].scale[0];
			cout << read_meshList[i].scale[1];
			cout << read_meshList[i].scale[2] << endl;

			cout << "\t";
			cout << "Vertex Count: ";
			cout << read_meshList[i].vertexCount << endl;
			//cout << "SkelAnimVert Count: 0" << endl;
			//cout << "Joint Count: 0"  << endl;

			cout << "\t";
			cout << "Material ID: ";
			cout << read_meshList[i].materialID << endl;
			//												detta är storleken av innehållet i vList.data()

			cout << "\n";
			cout << "Vertex vector: " << endl;

			read_mList.resize(read_mainHeader.meshCount);
			cout << "mlist: " << endl;
			read_mList[i].vList.resize(read_meshList[i].vertexCount);
			cout << "\t";
			cout << read_mList[i].vList.data() << endl;

			cout << "\t";
			cout << "Allocated memory for " << read_meshList[i].vertexCount << " vertices" << endl;

			read_mList[i].vList.resize(read_meshList[i].vertexCount);

			infile.read((char*)read_mList[i].vList.data(), sizeof(read_sVertex) * read_meshList[i].vertexCount);//				Skriver ut alla vertices i får vArray, pos, nor, rgba 100 gånger. Och minnet 100 Vertices tar upp.

																												//cout << "SkelAnimVert vector: NULL" << endl;

				 																							//cout << "Joint vector: NULL" << endl;
			cout << "______________________" << endl;
			GLuint vertexBuff;


			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			// It wörks
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);
			glEnableVertexAttribArray(4);

			glGenBuffers(1, &vertexBuff);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuff);
			glBufferData(GL_ARRAY_BUFFER, sizeof(read_sVertex) * read_mList[i].vList.size(), read_mList[i].vList.data(), GL_STATIC_DRAW);
			cout << "______________________" << endl;
		}
	}

	if (read_mainHeader.materialCount >= 1)
	{
		read_mMaterialList.resize(read_mainHeader.materialCount);

		for (int i = 0; i < read_mainHeader.materialCount; i++)
		{
			infile.read((char*)&read_mMaterialList[i], sizeof(read_sMaterial)); //Information av hur många material som senare kommer att komma, samt hur mycket minne den inten som berättar detta tar upp.

			cout << "Material: " << i << " Name: " << read_mMaterialList[i].materialName <<  endl;

			cout << "Material vector: " << endl;

			cout << "\t";
			cout << &read_mMaterialList[i] << endl;

			cout << "\t";
			cout << "Allocated memory for " << read_mainHeader.materialCount << " materials" << endl;

			cout << "\t";
			cout << "Ambient color: ";
			cout << read_mMaterialList[i].ambientColor[0] << " "
				<< read_mMaterialList[i].ambientColor[1] << " "
				<< read_mMaterialList[i].ambientColor[2] << " " << endl;

			cout << "\t";
			cout << "Diffuse color: ";
			cout << read_mMaterialList[i].diffuseColor[0] << " "
				<< read_mMaterialList[i].diffuseColor[1] << " "
				<< read_mMaterialList[i].diffuseColor[2] << " " << endl;

			cout << "\t";
			cout << "Specular color: ";
			cout << read_mMaterialList[i].specularColor[0] << " "
				<< read_mMaterialList[i].specularColor[1] << " "
				<< read_mMaterialList[i].specularColor[2] << " " << endl;

			cout << "\t";
			cout << "Shiny factor: ";
			cout << read_mMaterialList[i].shinyFactor << endl;

			cout << "\t";
			cout << "Diffuse texture: " << read_mMaterialList[i].diffuseTexture << endl;

			cout << "\t";
			cout << "Specular texture: " << read_mMaterialList[i].specularTexture << endl;

			cout << "\t";
			cout << "Normal texture: " << read_mMaterialList[i].normalTexture << endl;


			cout << "______________________" << endl;
		}

	}

	if (read_mainHeader.lightCount >= 1)
	{
		read_mLightList.resize(read_mainHeader.lightCount);

		for (int i = 0; i < read_mainHeader.lightCount; i++)
		{
			infile.read((char*)&read_mLightList[i], sizeof(read_sLight));

			cout << "Light: " << i << endl;

			cout << "Light vector: " << endl;

			cout << "\t";
			cout << &read_mLightList[i] << endl;

			cout << "\t";
			cout << "Allocated memory for " << read_mainHeader.lightCount << " lights" << endl;

			cout << "\t";
			cout << "Light ID: " << read_mLightList[i].lightID << endl;

			cout << "\t";
			cout << "Light position: " << read_mLightList[i].lightPos[0] << " "
				<< read_mLightList[i].lightPos[1] << " "
				<< read_mLightList[i].lightPos[2] << endl;

			cout << "\t";
			cout << "Light rotation: " << read_mLightList[i].lightRot[0] << " "
				<< read_mLightList[i].lightRot[1] << " "
				<< read_mLightList[i].lightRot[2] << endl;

			cout << "\t";
			cout << "Light scale: " << read_mLightList[i].lightScale[0] << " "
				<< read_mLightList[i].lightScale[1] << " "
				<< read_mLightList[i].lightScale[2] << endl;

			cout << "\t";
			cout << "Light color: " << read_mLightList[i].color[0] << " "
				<< read_mLightList[i].color[1] << " "
				<< read_mLightList[i].color[2] << " " << endl;

			cout << "\t";
			cout << "Light intensity: " << read_mLightList[i].intensity << endl;

			cout << "______________________" << endl;
		}
	}

	if (read_mainHeader.cameraCount >= 1)
	{
		read_mCameraList.resize(read_mainHeader.cameraCount);

		for (int i = 0; i < read_mainHeader.cameraCount; i++)
		{
			infile.read((char*)&read_mCameraList[i], sizeof(read_sCamera));
			cout << "Camera: " << i << endl;

			cout << "Camera vector: " << endl;

			cout << "\t";
			cout << &read_mCameraList[i] << endl;

			cout << "\t";
			cout << "Allocated memory for " << read_mainHeader.cameraCount << " cameras" << endl;

			cout << "\t";
			cout << "Camera position: " << read_mCameraList[i].camPos[0] << " "
				<< read_mCameraList[i].camPos[1] << " "
				<< read_mCameraList[i].camPos[2] << endl;

			cout << "\t";
			cout << "Camera Up vector: " << read_mCameraList[i].upVector[0] << " "
				<< read_mCameraList[i].upVector[1] << " "
				<< read_mCameraList[i].upVector[2] << endl;

			cout << "\t";
			cout << "FOV: " << read_mCameraList[i].fieldOfView << endl;

			cout << "\t";
			cout << "Near plane: " << read_mCameraList[i].nearPlane << endl;

			cout << "\t";
			cout << "Far plane: " << read_mCameraList[i].farPlane << endl;

			cout << "______________________" << endl;
		}
	}

	infile.close();
}