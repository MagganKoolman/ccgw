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
#include "Grid.h"
#include "Enemy.h"

class Game {
public:
	bool run(const Input* inputs, const float &dt);
	void tacticalRun(const Input* inputs, const float &dt);

	Game();
	~Game();
private:
	GameState* pActionState;
	GLuint testScreen;
	Terrain aBox;
	Terrain mGround;
	GameData data;
	sNode* mpPath;
	int mTargets;
	Enemy* mpEnemy;

	void createScreenQuad();
	void drawOnScreenQuad();
	void render();
	void update(const Input* inputs, float dt);
};
