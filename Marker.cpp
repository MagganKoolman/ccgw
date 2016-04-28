#include "Marker.h"
#include "Player.h"
#include "Tower.h"

void Marker::update(const Player* player) {
	float aRot = player->getRot() + glm::pi<float>() * 0.5f;
	glm::vec3 playerPos = player->getPosition();
	glm::vec3 lookAt = player->getLookAt();
	this->mWorld = {
		cosf(aRot), 0.0f, sinf(aRot), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sinf(aRot), 0.0f, cosf(aRot), 0.0f,
		playerPos.x + lookAt.x * 8,			playerPos.y + lookAt.y * 8,	playerPos.z + lookAt.z * 8,	1.0
	};
}

void Marker::update(const Input * inputs, GameData &gameData)
{
	selectedTile = mousePicking(inputs->mousePosition(), gameData) * (float)gameData.boxScale;
	uchar currrentTile = gameData.pGrid->getTile(selectedTile.x, selectedTile.y);
	if (inputs->buttonDown(0) && currrentTile == TILE_EMPTY)
	{		
		gameData.pGrid->setTile(selectedTile.x, selectedTile.y, TILE_HOLD);
		mMarkedIndex.push_back(selectedTile);
	}
	if (inputs->buttonDown(2) && currrentTile != TILE_EMPTY)
	{
		gameData.pGrid->setTile(selectedTile.x, selectedTile.y, TILE_EMPTY);
		for (int i = 0; i < mMarkedIndex.size(); i++) {
			if (mMarkedIndex[i] == selectedTile)
				mMarkedIndex.erase(mMarkedIndex.begin() + i);
		}	
	}
	if (inputs->keyDown(SDLK_1))
	{
		for (int i = 0; i < mMarkedIndex.size(); i++) {
			gameData.pGrid->setTile(mMarkedIndex[i].x, mMarkedIndex[i].y, TILE_BOX);
			//gameData.pTowers.push_back(new Tower(glm::vec3(mMarkedIndex[i].x, 0.0f, mMarkedIndex[i].y)));
		}	
		mMarkedIndex.clear();
	}
	mWorld[3][0] = selectedTile.x;
	mWorld[3][1] = 1.0f;
	mWorld[3][2] = selectedTile.y;
}

void Marker::render(const GLuint & programID)
{
	GLuint world = glGetUniformLocation(programID, "world");
	glUniformMatrix4fv(world, 1, GL_FALSE, &this->mWorld[0][0]);
	activateTextures(programID);
	mpMesh->draw();
	for (int i = 0; i < mMarkedIndex.size(); i++) {
		mWorld[3][0] = mMarkedIndex[i].x;
		mWorld[3][1] = 1.0f;
		mWorld[3][2] = mMarkedIndex[i].y;
		glUniformMatrix4fv(world, 1, GL_FALSE, &this->mWorld[0][0]);
		mpMesh->draw();
	}
	deactivateTextures();
}

glm::vec2 Marker::mousePicking(const glm::vec2 mousePos, const GameData &gameData) {
	float x = (2.0f * mousePos.x + 40) / gWidth - 1.0f;
	float y = 1.0f - (2.0f * mousePos.y + 60) / gHeight;
	glm::vec3 rayNDC = glm::vec3(x, y, 0);
	glm::vec4 rayClipSpace = glm::vec4(rayNDC.x, rayNDC.y, -1.0, 0.0);
	glm::vec4 rayEyeSpace = glm::inverse(gameData.pCamera->getPerspective()) * rayClipSpace;
	rayEyeSpace = glm::vec4(rayEyeSpace.x, rayEyeSpace.y, -1.0, 0.0);
	glm::vec4 rayWorldSpace = glm::inverse(gameData.pCamera->getView()) * rayEyeSpace;
	rayWorldSpace = glm::normalize(rayWorldSpace);
	float scalar = -(gameData.pCamera->getPosition().y - 0.5) / rayWorldSpace.y;
	rayWorldSpace *= scalar;
	glm::vec2 pickPos;
	pickPos.x = (int)(gameData.pCamera->getPosition().x/gameData.boxScale + rayWorldSpace.x);
	pickPos.y = (int)(gameData.pCamera->getPosition().z/gameData.boxScale + rayWorldSpace.z);
	//std::cout << pickPos.x << "    " << pickPos.y << "\n";
	return pickPos;
}

Marker::Marker()
{
	mPicked = false;
	selectedTile = { -1, -1 };
}

Marker::~Marker()
{

}
