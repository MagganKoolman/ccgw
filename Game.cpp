#include "Game.h"
#include <random>

struct ScreenVertex 
{
	float x, y, s, t;
};

void Game::createScreenQuad() 
{
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

void Game::drawOnScreenQuad()
{
	glBindBuffer(GL_ARRAY_BUFFER, testScreen);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ScreenVertex), (void*)offsetof(ScreenVertex, x));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ScreenVertex), (void*)offsetof(ScreenVertex, s));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Game::Game() /*mCamera(45.0f, (float)gWidth/gHeight, 0.5, 50), mPlayer(&mAssets)*/
{
	pActionState = nullptr;
	mStateTransition = false;
	createScreenQuad();

	data.pAssets = new Assets();
	data.pCamera = new Camera( 45.0f, (float)gWidth/gHeight, 0.5f, 50.0f );
	data.pDeferredProgram = new DeferredProgram("deferred.vertex", "deferred.pixel", "deferred.geometry");
	data.pForwardProgram = new ForwardProgram("forward.vertex", "forward.pixel", " ");
	data.pBillboardProgram = new BillboardProgram("billboard.vertex", "billboard.pixel", "billboard.geometry");
	data.pEmission = new Emission(&data, 1000);
	data.pPlayer = new Player(&data);
	data.boxScale = 2;
	/*if( data.pEmission->allocEmitter( &pEmitter, 10 ) )
		pEmitter.load( &data, "Models/pns.png" );*/

	tempMesh* playerModel = data.pAssets->load<tempMesh>( "Models/box2.obj" );
	Texture* groundTexture = data.pAssets->load<Texture>( "Models/ground.png" );
	Texture* playerTexture = data.pAssets->load<Texture>( "Models/cube.png" );
	Texture* specMap = data.pAssets->load<Texture>("Models/specMap.png");
	Texture* normalMap = data.pAssets->load<Texture>("Models/tegelNormal.png");

	data.pGrid = new Grid(20, 20, playerModel);

	sNode start = { 0, 0 };
	sNode end = { 2, 2 };
	mpPath = new sNode[20*20];
	mTargets = 0;

	data.pGrid->findPath( start, end, mpPath, &mTargets );

	data.pPlayer->load( playerModel, playerTexture, specMap, normalMap);
	mGround.load(data.pAssets->load<tempMesh>("Models/plane.obj"), groundTexture, specMap, nullptr);
	mActionMarker.load(data.pAssets->load<tempMesh>("Models/marker.obj"), groundTexture, specMap, nullptr);
	mTacticalMarker.load(playerModel, groundTexture, specMap, nullptr);
	mTacticalMarker.setScale(data.boxScale);
	mTowerModel.load(playerModel, groundTexture, nullptr, nullptr);
}

Game::~Game() {
	delete data.pDeferredProgram;
	delete data.pForwardProgram;
	delete data.pBillboardProgram;
	delete data.pPlayer;
	delete data.pCamera;
	delete data.pEmission;
	delete data.pGrid;
	delete pActionState;
	delete[] mpPath;

	data.pAssets->unload();
	delete data.pAssets;
}

 bool Game::run(const Input* inputs, const float &dt) 
 {
	update(inputs, dt);
	render();
	return true;
}

 void Game::tacticalRun(const Input* inputs, const float &dt) 
 {
	 if (mStateTransition) {
		 glm::vec3 dPosition = (glm::vec3(0, 20, 0) - (data.pCamera->getPosition() - glm::vec3(0, -1, 0))) * (5 * dt);
		 this->data.pCamera->follow(data.pCamera->getPosition() + dPosition - glm::vec3(0, 1, 0), { 0,-1,0 }, 1, { 0,0,-1 });
		 if (data.pCamera->getPosition().y > 15)
			 mStateTransition = false;
	 }
	 else {
		data.pCamera->tacticalMovement(data.pPlayer->tacticalUpdate(inputs, dt, data), 20);	
		mTacticalMarker.update(inputs, data);
	}
	render();
 }

 void Game::setTransition(bool state)
 {
	 mStateTransition = state;
 }


void Game::render()
{
	data.pDeferredProgram->use();
	data.pCamera->updateUniforms( data.pDeferredProgram->getViewPerspectiveLocation(), data.pDeferredProgram->getCameraPositionLocation() );
	data.pPlayer->render( data.pDeferredProgram->getProgramID(), data.pCamera->getView());
	
	for (int i = 0; i < data.pTowers.size(); i++)
		data.pTowers[i]->render(data.pDeferredProgram->getProgramID());
	mGround.render( data.pDeferredProgram->getProgramID() );
	data.pGrid->debugRender( data.pDeferredProgram->getProgramID() );
	if(data.pCamera->getPosition().y < 15)
		mActionMarker.render(data.pDeferredProgram->getProgramID());
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mTacticalMarker.render(data.pDeferredProgram->getProgramID());
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	data.pBillboardProgram->use();
	data.pBillboardProgram->begin( data.pCamera );

	data.pEmission->draw();
	data.pBillboardProgram->end();
	data.pBillboardProgram->unUse();
	data.pDeferredProgram->unUse();

	data.pForwardProgram->use();
	data.pDeferredProgram->enableTextures(data.pForwardProgram->getProgramID());

	GLuint cameraPos = glGetUniformLocation(data.pForwardProgram->getProgramID(), "cameraPos");
	glUniform3fv(cameraPos, 1, &data.pCamera->getPosition()[0]);
	GLuint inverseViewPerspective = glGetUniformLocation(data.pForwardProgram->getProgramID(), "invViewPerspective");
	glUniformMatrix4fv(inverseViewPerspective, 1, GL_FALSE, &glm::inverse(data.pCamera->getViewPerspective())[0][0]);

	drawOnScreenQuad();
	data.pDeferredProgram->disableTextures();
	data.pForwardProgram->unUse();
}

void Game::update(const Input* inputs, float dt) 
{
	data.pPlayer->update(inputs, dt);
	data.pEmission->update(dt);
	data.pCamera->follow(data.pPlayer->getPosition(), data.pPlayer->getLookAt(), 5, {0,1,0});
	mActionMarker.update(data.pPlayer);
}

void Game::createWave() {
	
}