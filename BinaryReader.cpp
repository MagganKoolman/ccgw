
#include <GL\glew.h>
#include <fstream>
#include <vector>
#include <iostream>
#include "ReadHeaderData.h"
#include "BinaryReader.h"

using namespace std;

void BinaryReader::readFromBinary(GLuint &vao)
{
	/*Reading the binary file that we just have been written to.*/

	std::ifstream infile("testBin.bin", std::ifstream::binary);

	cout << ">>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<" << "\n" << "\n" << endl;
	cout << "Binary Reader" << endl;
	cout << "\n" << endl;

	/*Reading the first block of memory that is the main header. This will read
	information about how much of each node type we have from a imported scene and
	how memory they will take up in the binary file.*/

	infile.read((char*)&read_gMainHeader, sizeof(read_sMainHeader));

	cout << "______________________" << endl;
	cout << "Main Header" << endl;
	cout << "meshCount: " << read_gMainHeader.meshCount << endl;
	cout << "materialCount: " << read_gMainHeader.materialCount << endl;
	cout << "lightCount: " << read_gMainHeader.lightCount << endl;
	cout << "cameraCount: " << read_gMainHeader.cameraCount << endl;
	cout << "______________________" << endl;


	read_meshList.resize(read_gMainHeader.meshCount);

	for (int i = 0; i < read_gMainHeader.meshCount; i++)
	{
		cout << "Mesh: " << i << endl;

		/*Reading the block of memory that is the meshes. The information from the meshes
		will be read here, that includes for example vertex count for a normal mesh
		and a skinned mesh. What we do is reserving memory for all the data that is in the
		struct. For example, Vertex count is a integer and will take up to 4 bytes in the
		memory when reading.*/

		infile.read((char*)&read_meshList[i], sizeof(read_sMesh));

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

		/*Do we need to have some kind of special treatment when writing
		the meshes that have skinning???*/

		/*cout << "SkelAnimVert Count: 0" << endl;
		cout << "Joint Count: 0"  << endl;*/

		cout << "\t";
		cout << "Material ID: ";
		cout << read_meshList[i].materialID << endl;

		cout << "\n";
		cout << "Vertex vector: " << endl;

		read_mList.resize(read_gMainHeader.meshCount);
		cout << "mlist: " << endl;
		read_mList[i].vList.resize(read_meshList[i].vertexCount);
		cout << "\t";
		cout << read_mList[i].vList.data() << endl;

		cout << "\t";
		cout << "Allocated memory for " << read_meshList[i].vertexCount << " vertices" << endl;

		read_mList[i].vList.resize(read_meshList[i].vertexCount);

		/*Reading all the vertex lists for each mesh. For example if a mesh have 200 vertices,
		we can multiply the count of vertices with the sizes in bytes that the sVertex struct have.
		This means that we will be reading the pos, nor, uv, tan, bitan 200 times.*/
		infile.read((char*)read_mList[i].vList.data(), sizeof(read_sVertex) * read_meshList[i].vertexCount);

		cout << "______________________" << endl;
	}

	read_mMaterialList.resize(read_gMainHeader.materialCount);

	for (int i = 0; i < read_gMainHeader.materialCount; i++)
	{
		cout << "Material: " << i << endl;

		cout << "Material vector: " << endl;

		cout << "\t";
		cout << &read_mMaterialList[i] << endl;

		cout << "\t";
		cout << "Allocated memory for " << read_gMainHeader.materialCount << " materials" << endl;
		
		/*Reading all the materials from the list with the size in bytes in mind.*/
		infile.read((char*)&read_mMaterialList[i], sizeof(read_sMaterial));

		cout << "______________________" << endl;
	}

	read_mLightList.resize(read_gMainHeader.lightCount);

	for (int i = 0; i < read_gMainHeader.lightCount; i++)
	{
		cout << "Light: " << i << endl;

		cout << "Light vector: " << endl;

		cout << "\t";
		cout << &read_mLightList[i] << endl;

		cout << "\t";
		cout << "Allocated memory for " << read_gMainHeader.lightCount << " lights" << endl;

		/*Reading all the lights from the list with the size in bytes in mind.*/
		infile.read((char*)&read_mLightList[i], sizeof(read_sLight));

		cout << "______________________" << endl;
	}

	read_mCameraList.resize(read_gMainHeader.cameraCount);

	for (int i = 0; i < read_gMainHeader.cameraCount; i++)
	{
		cout << "Camera: " << i << endl;

		cout << "Camera vector: " << endl;

		cout << "\t";
		cout << "Allocated memory for " << read_gMainHeader.cameraCount << " cameras" << endl;

		/*Reading all the cameras from the list with the size in bytes in mind.*/
		infile.read((char*)&read_mCameraList[i], sizeof(read_sCamera));

		cout << "______________________" << endl;
	}

	infile.close();
}