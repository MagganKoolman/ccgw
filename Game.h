#pragma once
#include "GameState.h"
#include "DeferredProgram.h"
#include "ForwardProgram.h"
#include "TestSprite.h"
#include "tempMesh.h"


class Game {
public:
	bool update();

	Game();
	~Game();
private:
	GameState* pActionState;
	ShaderProgram* pDeferredProgram;
	ShaderProgram* pForwardProgram;
	
	TestSprite tSprite;
	GLuint testScreen;

	tempMesh playerModel;

	void createScreenQuad();
	void drawOnScreenQuad();
	void render();
};
