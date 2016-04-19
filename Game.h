#pragma once
#include "ActionState.h"
#include "DeferredProgram.h"
#include "ForwardProgram.h"
#include "tempMesh.h"
#include "Player.h"
#include "Input.h"
#include "Camera.h"
#include "global_variables.h"
#include "Terrain.h"
#include "Texture.h"
#include "Billboard.h"
#include "Emitter.h"

class Game {
public:
	bool run(const Input* inputs, const int &dt);

	Game();
	~Game();
private:
	GameState* pActionState;
	GLuint testScreen;
	Terrain aBox;
	Terrain mGround;
	GameData data;

	void createScreenQuad();
	void drawOnScreenQuad();
	void render();
	void update(const Input* inputs);
};
