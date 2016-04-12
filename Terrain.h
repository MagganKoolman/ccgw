#pragma once
#include "GameObject.h"

class Terrain :public GameObject {
public:
	void render(const GLuint &programID);

	Terrain();
	~Terrain();
private:

};