#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include "raymath.h"

#include "inputManager.h"
#include "physicsUtilities.h"
#include "constants.h"
#include "circle.h"				// for collision detection later.

// A particle is a point mass

class Particle
{
	
private:
	Vector2 position;			// the coordinate of the center of the particle, in terms of meters.
	Vector2 velocity;			// the velocity of the particle, in terms of meters per second.
	Vector2 acceleration;		// the acceleration of the particle, in terms of meters per seconds square.
	
	Vector2 accumulatedForce;	// apply this force by updating acceleration. Only applied once per frame. Reset to zero once applied.
	
	float mass;					// the mass of the particle in kg.
	float radius;				// since particle is a cirle, it has a radius, measured in meters.
	float radiusPixel;			// measured in pixels.	
	Color color;				// the color of the particle. (since the particle is a circle, it has this color.)
	
	float restitution;			// the coefficient of restitution. e = velocity of seperation / velocity of approach.

	
	bool isGravityOn;			// true means gravitational force vector {0, mass*GRAVITY} is added to accumulatedForce each frame.
	
	// Helper Functions ======================================================================================================
	
	void UpdateAcceleration();
	void UpdateVelocity(float dt);
	void UpdatePosition(float dt);
	void ApplyGravity();
	void ClearForces();
	
public:
	// Constructors ==========================================================================================================
	
	Particle();
	
	// Getters ===============================================================================================================
	
	Vector2 GetPosition() const;						// get position vector in m.
	Vector2 GetVelocity() const;						// get velocity vector in m/s.
	Vector2 GetAcceleration() const;					// get acceleration vector in m/s2.
	
	Vector2 GetAccumulatedForce() const;				// get accumulatedForce vector in Newtons.
	
	float GetMass() const;								// get mass in kg.
	float GetRadius() const;							// get radius in m.
	
	float GetRestitution() const;							// get the coefficient of restitution.
	
	Circle GetCircle() const;							// for collision detection. Acts as a hit box.
	
	// Setters ===============================================================================================================
	
	void SetPosition(Vector2 newPosition);				// set in m.
	void SetVelocity(Vector2 newVelocity);				// set in m/s.
	void SetAcceleration(Vector2 newAcceleration);		// set in m/s2.
	
	void SetMass(float newMass);						// set in kg.
	void SetRadius(float newRadius);					// set in m. Updates radiusPixel too.	
	void SetColor(Color newColor);						// set the color of the particle circle.
	
	void SetRestitution(float newRestitution);			// set the coefficient of restitution.
	
	void SetGravityStatus(bool status);					// set bool.

	void ApplyForce(Vector2 forceVector);				// force in Newtons. Updates the accumulatedForce.
	
	
	
	
	void Input(const InputManager& input);
	
	
	void Update(float dt);								// apply the accumulatedForce by updating acceleration, velocity, and position.
	
	void Draw() const;
	
};

#endif
