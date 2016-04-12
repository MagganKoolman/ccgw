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


class Game {
public:
	bool run(const Input* inputs);

	Game();
	~Game();
private:
	GameState* pActionState;
	ShaderProgram* pDeferredProgram;
	ShaderProgram* pForwardProgram;
	
	GLuint testScreen;

	tempMesh playerModel;
	tempMesh terrainModel;
	Player mPlayer;
	Terrain mGround;

	Camera mCamera;

	void createScreenQuad();
	void drawOnScreenQuad();
	void render();
	void update(const Input* inputs);
};
