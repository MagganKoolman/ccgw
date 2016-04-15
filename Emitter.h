#pragma once

#include "Particle.h"
#include "Billboard.h"

/*Class for emitting particles.*/
class Emitter
{
public:
	/*Loads all the particles with the supplied texture.*/
	bool load( GameData* data, string texture );
	/*Spawns one of the particles at the emitters position.*/
	void spawn( glm::vec3 velocity, float lifeftime, float drag = 0.5f, glm::vec2 startScale = glm::vec2(1.0f), glm::vec2 endScale = glm::vec2(1.0f) );
	/*Updates the position, velocity, scale and lifetime of all particles.*/
	void update( float deltaTime );
	/*Draws all particles.*/
	void draw();

	void setPosition( glm::vec3 position );
	glm::vec3 getPosition() const;

	Emitter& operator=( const Emitter& ref );
	Emitter( const Emitter& ref );
	Emitter( int maxParticles );
	~Emitter();

private:
	void sort();

	Camera* mpCamera;
	BillboardProgram* mpBillboardProgram;

	Particle* mpParticles;
	Particle** mpSorted;
	int mMax;
	int mAlive;
	float* mDistances;

	glm::vec3 mPosition;
};