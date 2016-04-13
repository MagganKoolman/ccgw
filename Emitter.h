#pragma once

#include "Particle.h"
#include "Billboard.h"

/*Class for emitting particles.*/
class Emitter
{
public:
	/*Loads all the particles with the supplied texture.*/
	bool load( Assets* assets, string texture );
	/*Spawns one of the particles at the emitters position.*/
	void spawn( glm::vec3 velocity, float lifeftime, glm::vec2 startScale = glm::vec2(1.0f), glm::vec2 endScale = glm::vec2(1.0f), float drag = 0.5f );
	/*Updates the position, velocity, scale and lifetime of all particles.*/
	void update( float deltaTime );
	/*Draws all particles.*/
	void draw();

	void setPosition( glm::vec3 position );
	glm::vec3 getPosition() const;

	Emitter& operator=( const Emitter& ref );
	Emitter( const Emitter& ref );
	Emitter( Camera* camera, BillboardProgram* billboardProgram, int maxParticles );
	~Emitter();

private:
	Camera* mpCamera;
	BillboardProgram* mpBillboardProgram;

	Particle* mpParticles;
	int mMax;

	glm::vec3 mPosition;
};