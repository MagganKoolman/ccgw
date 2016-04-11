#pragma once
#include "ActionState.h"
#include "DeferredProgram.h"
#include "ForwardProgram.h"
#include "TestSprite.h"
#include "tempMesh.h"
#include "Player.h"
#include "Input.h"


class Game {
public:
	bool run(const Input* inputs);

	Game();
	~Game();
private:
	GameState* pActionState;
	ShaderProgram* pDeferredProgram;
	ShaderProgram* pForwardProgram;
	
	TestSprite tSprite;
	GLuint testScreen;

	tempMesh playerModel;
	Player mPlayer;

	void createScreenQuad();
	void drawOnScreenQuad();
	void render();
	void update(const Input* inputs);
};
