#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include "raymath.h"
#include "inputManager.h"
#include "physicsUtilities.h"

// A particle is a point mass

class Particle
{
	
private:
	Vector2 position;			// the coordinate of the center of the particle, in terms of meters.
	Vector2 velocity;
	Vector2 acceleration;
	
	Vector2 accumulatedForce;
	
	float mass;
	float radius;				// since particle is a cirle, it has a radius, measured in meters.
	float radiusPixel;			// measured in pixels.
	
	// Helper Functions ======================================================================================================
	
	void UpdateAcceleration();
	void UpdateVelocity(float dt);
	void UpdatePosition(float dt);
	void ClearForces();
	
public:
	// Constructors ==========================================================================================================
	
	Particle();
	
	// Getters ===============================================================================================================
	
	Vector2 GetPosition() const;
	Vector2 GetVelocity() const;
	Vector2 GetAcceleration() const;
	
	Vector2 GetAccumulatedForce() const;
	
	// Setters ===============================================================================================================
	
	void SetPosition(Vector2 newPosition);
	void SetVelocity(Vector2 newVelocity);
	void SetAcceleration(Vector2 newAcceleration);
	
	void ApplyForce(Vector2 force);
	
	
	void Input(const InputManager& input);
	
	
	void Update(float dt);
	
	void Draw() const;
	
};

#endif
