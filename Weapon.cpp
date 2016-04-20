#include "Weapon.h"

void Weapon::shoot(glm::vec3 position, glm::vec3 lookat, float rotation) 
{
	bool shot = false;
	for (int i = 0; i < mMax && !shot; i++) {
		if (!arrows[i].isAlive()) {
			arrows[i].spawn(position, lookat,15*mStrength, { 0,-1,0 }, rotation);
			shot = true;
		}
	}
	this->mStrength = 0;
}
void Weapon::update(bool hold, float dt) {
	if (hold)
		this->mStrength += dt;
	for (int i = 0; i < mMax; i++) {
		if(arrows[i].isAlive())
			arrows[i].update(dt);
	}
}

void Weapon::draw(const GLuint &programID) {
	for (int i = 0; i < mMax; i++) {
		if (arrows[i].isAlive())
			arrows[i].render(programID);
	}
}

Weapon::Weapon(GameData* data) 
{
	Texture* tex = data->pAssets->load<Texture>("Models/pns.png");
	mMax = 100;
	this->arrows = new Arrow[mMax];
	for (int i = 0; i < mMax; i++)
	{
		this->arrows[i].loadTex(tex);
		this->arrows[i].load( data, "Models/box2.obj");
	}
	this->mStrength = 0;
}

Weapon::~Weapon() 
{
	delete[] arrows;
}