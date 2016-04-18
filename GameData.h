#pragma once

#include <vector>

class Assets;
class Camera;
class DeferredProgram;
class ForwardProgram;
class BillboardProgram;
class Player;
class Emission;
struct GameData
{
	Assets* pAssets;
	Camera* pCamera;
	DeferredProgram* pDeferredProgram;
	ForwardProgram* pForwardProgram;
	BillboardProgram* pBillboardProgram;
	Player* pPlayer;
	Emission* pEmission;
};
