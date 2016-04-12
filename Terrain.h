#pragma once
#include "GameObject.h"

class Terrain :public GameObject {
public:
	bool load(tempMesh* assets);
	void render(const GLuint &programID);

	Terrain();
	~Terrain();
private:

};