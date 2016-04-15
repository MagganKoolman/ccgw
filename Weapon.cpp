#include "Weapon.h"

void Weapon::shoot(glm::vec3 position, glm::vec3 lookat) 
{
	if (mTimeSinceLastShot > mReloadTime)
	{
		bool shot = false;
		for (int i = 0; i < mMax && !shot; i++) {
			if (!arrows[i].isAlive()) {
				arrows[i].spawn(position, lookat, 5, { 0,-1,0 });
				shot = true;
			}
		}
	}
}
void Weapon::update(float dt) {
	this->mTimeSinceLastShot += dt;
	for (int i = 0; i < mMax; i++) {
		arrows[i].update(dt);
	}
}

void Weapon::draw(const GLuint &programID) {
	for (int i = 0; i < mMax; i++) {
		if (arrows[i].isAlive())
			arrows[i].render(programID);
	}
}

Weapon::Weapon(float rt, GameData* data) 
{
	Texture* tex = data->pAssets->load<Texture>("Models/pns.png");
	mMax = 10;
	for (int i = 0; i < mMax; i++)
	{
		this->arrows[i].loadTex(tex);
		this->arrows[i].load( data, "Models/box2.obj");
	}
	this->mReloadTime = rt;
	this->mTimeSinceLastShot = 0;
}

Weapon::~Weapon() 
{

}