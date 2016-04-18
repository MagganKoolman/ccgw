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

Game::Game() /*mCamera(45.0f, (float)gWidth/gHeight, 0.5, 50), mPlayer(&mAssets)*/{
	pActionState = nullptr;
	/*pDeferredProgram = new DeferredProgram("deferred.vertex","deferred.pixel","deferred.geometry");
	pForwardProgram = new ForwardProgram("forward.vertex", "forward.pixel", " ");
	pBillboardShader = new BillboardProgram( "billboard.vertex", "billboard.pixel", "billboard.geometry" );
	pEmitter = new Emitter( &mCamera, pBillboardShader, 1000 );
	pEmitter->load( &mAssets, "Models/pns.png" );*/

	createScreenQuad();

	/*tempMesh* playerModel = mAssets.load<tempMesh>( "Models/box2.obj" );
	tempMesh* terrainModel = mAssets.load<tempMesh>( "Models/plane.obj" );
	Texture* texture = mAssets.load<Texture>( "Models/ground.png" );
	Texture* texture2 = mAssets.load<Texture>( "Models/cube.png" );


	mPlayer.load(playerModel);	
	mGround.load(terrainModel);
	mPlayer.loadTex(texture2);
	mGround.loadTex(texture);
	aBox.load(playerModel);
	aBox.loadTex(texture);*/

	data.pAssets = new Assets();
	data.pCamera = new Camera( 45.0f, (float)gWidth/gHeight, 0.5f, 50.0f );
	data.pDeferredProgram = new DeferredProgram("deferred.vertex", "deferred.pixel", "deferred.geometry");
	data.pForwardProgram = new ForwardProgram("forward.vertex", "forward.pixel", " ");
	data.pBillboardProgram = new BillboardProgram("billboard.vertex", "billboard.pixel", "billboard.geometry");
	data.pPlayer = new Player( &data );

	tempMesh* playerModel = data.pAssets->load<tempMesh>( "Models/box2.obj" );
	tempMesh* terrainModel = data.pAssets->load<tempMesh>( "Models/plane.obj" );
	Texture* texture = data.pAssets->load<Texture>( "Models/ground.png" );
	Texture* texture2 = data.pAssets->load<Texture>( "Models/cube.png" );

	data.pPlayer->load( playerModel );
	data.pPlayer->loadTex( texture2 );
	mGround.load( terrainModel );
	mGround.loadTex( texture );
	aBox.load( playerModel );
	aBox.loadTex( texture );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

Game::~Game() {
	delete data.pDeferredProgram;
	delete data.pForwardProgram;
	delete data.pBillboardProgram;
	//delete pEmitter;
	delete pActionState;
}

bool Game::run(const Input* inputs) {
	update(inputs);
	render();
	return true;
}

void Game::render() {
	data.pDeferredProgram->use();
	//mCamera.update(pDeferredProgram->getProgramID());
	data.pCamera->updateUniforms( data.pDeferredProgram->getViewPerspectiveLocation(), data.pDeferredProgram->getCameraPositionLocation() );
	data.pPlayer->render( data.pDeferredProgram->getProgramID(), data.pCamera->getView());
	aBox.render( data.pDeferredProgram->getProgramID() );
	mGround.render( data.pDeferredProgram->getProgramID() );

	data.pBillboardProgram->use();
	data.pBillboardProgram->begin( data.pCamera );
	//pEmitter->draw();

	for( std::vector<Emitter*>::const_iterator it = data.mEmitters.begin(); it != data.mEmitters.end(); it++ )
		(*it)->draw();

	data.pBillboardProgram->end();
	data.pBillboardProgram->unUse();

	data.pDeferredProgram->unUse();

	data.pForwardProgram->use();
	data.pDeferredProgram->enableTextures(data.pForwardProgram->getProgramID());
	drawOnScreenQuad();
	data.pDeferredProgram->disableTextures();
	data.pForwardProgram->unUse();
}

void Game::update(const Input* inputs) {
	data.pPlayer->update(inputs, 0.08f);
	//pEmitter->setPosition( mPlayer.getPosition() );
	data.pCamera->follow( data.pPlayer->getPosition(), data.pPlayer->getLookAt(), 5);

	// NOTE: Debug
	float x = (float)( rand() % 100 - 50 );
	float z = (float)( rand() % 100 - 50 );
	glm::vec3 v = glm::normalize( glm::vec3( x, 50.0f, z ) ) * 0.25f;
	//pEmitter->spawn( v, 2.0f, 0.1f, glm::vec2( 0.5f ), glm::vec2( 0.0f ) );
	//pEmitter->update( 0.01f );
}