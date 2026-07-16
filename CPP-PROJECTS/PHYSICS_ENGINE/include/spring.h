#ifndef SPRING_H
#define SPRING_H

#include "raylib.h"
#include "raymath.h"

#include "inputManager.h"
#include "particle.h"
#include "physicsUtilities.h"


// F = K * e , where F is the force applied to the spring, k is the spring constant, and e is the extention of the spring
// length of the spring at a given moment is equal to the distance between it's two end points
// extention (e) of the spring at a given moment is equal to: currentLength - restLength

// F = -kx

// F = ma

// Spring Class ==============================================================================================================

class Spring
{
	
private:
	float restLength;				// the resting length of the spring in meters.
	float restLengthPixel;			// the resting length of the spring in pixels.
	
	float currentLength;			// the current length of the spring in meters.
	float currentLengthPixel;		// the current length of the spring in pixels.
	
	float extension;				// the extention of the spring in meters.
	float extensionPixel;			// the extention of the spring in pixels.
	
	float maxLength;				// the max length the spring can extend, in meters. (should this even be a thing to consider?)
	float maxLengthPixel;			// the max length the spring can extend, in pixels. (should this even be a thing to consider?)
	
	float springConstant;			// the spring stiffness in N/m.
	float dampingCoefficient;
	
	float forceOfSpring;			// the force produced by the spring due to its extention, using hooke's law.
	
	Particle* particleA;			// convention is that this is the particle on the right of the spring (atleast, initially).
	Particle* particleB;			// convention is that this is the particle on the left of the spring (atleast, initially).
	
	// The force on particles exerted by the spring:
	Vector2 forceOnParticleA;
	Vector2 forceOnParticleB;
	
	Vector2 endACoordinate;			// a coordinate, in terms of the pixels on the screen. The vector OA.
	Vector2 endBCoordinate;			// a coordinate, in terms of the pixels on the screen. The vector OB.
	
	// The end point vectors:
	Vector2 vectorFromAToB;			// the vector AB, equal to AO + OB = OB - OA.
	Vector2 vectorFromBToA;			// the vector BA, equal to -AB.
	
	
	// Helper Functions ======================================================================================================
	
	void UpdateEndPoints();			// updates endACoordinate and endBCoordinate through the particleA and particleB pointers
	void UpdateEndPointVectors();	// updates vectorFromAToB and vectorFromBToA
	void UpdateCurrentLength();		// calculates distance btw end points to update currentLengthPixel and currentLength
	void UpdateExtension();			// updates extension and extensionPixel
	void UpdateForceOfSpring();		// updates forceOfSpring
	void UpdateForceOnParticles();	// updates forceOnParticleA and forceOnParticleB
	void ApplyForceOnParticles();
	
	
	
	
	
public:
	
	// Constructors ==========================================================================================================
	
	Spring();
	
	// Getters ===============================================================================================================
	
	
	// Setters ===============================================================================================================
	
	void SetParticles(Particle* newParticleA, Particle* newParticleB);
	void SetParticleA(Particle* newParticleA);
	void SetParticleB(Particle* newParticleB);
	
	void SetRestLength(float restLength);
	
	void SetSpringConstant(float newSpringConstant);
	void SetDampingCoefficient(float newDampingCoefficient);
	
	// Base Functions ========================================================================================================
	
	void Input(const InputManager& input);
	
	void Update(float dt);
	
	void Draw() const;
};


#endif
