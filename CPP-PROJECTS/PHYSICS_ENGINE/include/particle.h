#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"

// A particle is a point mass

class Particle
{
	
private:
	Vector2 position;			// the coordinate of the center of the particle
	
	float mass;
public:
	Particle();
	
	Vector2 GetPosition() const;
	
};

#endif
