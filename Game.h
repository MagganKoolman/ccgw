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
	bool run(const Input* inputs);

	Game();
	~Game();
private:
	GameState* pActionState;
	ShaderProgram* pDeferredProgram;
	ShaderProgram* pForwardProgram;
	BillboardProgram* pBillboardShader;
	
	GLuint testScreen;

	Assets mAssets;
	//tempMesh playerModel;
	//tempMesh terrainModel;
	//Texture texture;
	//Texture texture2;
	Player mPlayer;
	Terrain aBox;
	Terrain mGround;

	Camera mCamera;

	Emitter* pEmitter;

	void createScreenQuad();
	void drawOnScreenQuad();
	void render();
	void update(const Input* inputs);
};
