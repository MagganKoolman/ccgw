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

Weapon::Weapon(float rt, Assets* assets) 
{
	Texture* tex = assets->load<Texture>("Models/pns.png");
	mMax = 20;
	arrows = new Arrow[mMax];
	for (int i = 0; i < mMax; i++)
	{
		this->arrows[i].loadTex(tex);
		this->arrows[i].load(assets, "Models/box2.obj");
	}
	this->mReloadTime = rt;
	this->mTimeSinceLastShot = 0;
}

Weapon::~Weapon() 
{
	delete[] arrows;
}