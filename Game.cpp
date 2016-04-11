#include "Game.h"

struct ScreenVertex {
	float x, y, s, t;
};

void Game::createScreenQuad() {
	glGenBuffers(1, &testScreen);
	ScreenVertex vertexData[6];
	vertexData[0].x = -1.0; vertexData[0].y = -1.0; vertexData[0].s = 0.0; vertexData[0].t = 0.0;
	vertexData[1].x = -1.0; vertexData[1].y = 1.0; vertexData[1].s = 0.0; vertexData[1].t = 1.0;
	vertexData[2].x = 1.0; vertexData[2].y = -1.0; vertexData[2].s = 1.0; vertexData[2].t = 0.0;
	vertexData[3].x = 1.0; vertexData[3].y = -1.0; vertexData[3].s = 1.0; vertexData[3].t = 0.0;
	vertexData[4].x = 1.0; vertexData[4].y = 1.0; vertexData[4].s = 1.0; vertexData[4].t = 1.0;
	vertexData[5].x = -1.0; vertexData[5].y = 1.0; vertexData[5].s = 0.0; vertexData[5].t = 1.0;
	glBindBuffer(GL_ARRAY_BUFFER, testScreen);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Game::drawOnScreenQuad() {
	glBindBuffer(GL_ARRAY_BUFFER, testScreen);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ScreenVertex), (void*)offsetof(ScreenVertex, x));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ScreenVertex), (void*)offsetof(ScreenVertex, s));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Game::Game() {
	pDeferredProgram = new DeferredProgram("deferred.vertex","deferred.pixel","deferred.geometry");
	pForwardProgram = new ForwardProgram("forward.vertex", "forward.pixel", " ");

	createScreenQuad();
	tSprite.init(0.5, 0.5, 1.0, 0.8);
	playerModel.load("Models/box2.obj");
	mPlayer.load(&playerModel);	
}

Game::~Game() {
	delete pDeferredProgram;
	delete pForwardProgram;
}

bool Game::run() {
	update();
	render();
	return true;
}

void Game::render() {
	pDeferredProgram->use();
	tSprite.draw(pDeferredProgram->getProgramID());
	mPlayer.render(pDeferredProgram->getProgramID());
	pDeferredProgram->unUse();

	pForwardProgram->use();
	dynamic_cast<DeferredProgram*> (pDeferredProgram)->enableTextures(pForwardProgram->getProgramID());
	drawOnScreenQuad();
	dynamic_cast<DeferredProgram*> (pDeferredProgram)->disableTextures();
	pForwardProgram->unUse();
}

void Game::update() {
	mPlayer.update(&mInputs);
}