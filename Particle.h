#pragma once

#include <glm\glm.hpp>
#include "Texture.h"

class Particle
{
public:
	/*Loads a texture for the particle.*/
	bool load( Assets* assets, string texture );
	/*Spawns the particle at the supplied position.*/
	void spawn( glm::vec3 position, glm::vec3 velocity, float lifetime, glm::vec2 startScale, glm::vec2 endScale, float drag );
	/*Updates the position, velocity, scale and lifetime of the particle.*/
	void update( float deltaTime );
	/*Draws the particle.*/
	void draw();

	float getLifetime() const;
	float getElapsed() const;
	
	Particle& operator=( const Particle& ref );
	Particle( const Particle& ref );
	Particle();
	~Particle();

private:
	glm::vec3 mPosition;
	glm::vec3 mVelocity;
	glm::vec2 mScale;

	glm::vec2 mStartScale;
	glm::vec2 mEndScale;
	float mLifetime, mElapsed, mDrag;

	Texture* mpTexture;
};