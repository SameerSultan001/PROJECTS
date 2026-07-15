#ifndef SPRING_H
#define SPRING_H

#include "raylib.h"
#include "inputManager.h"
#include "particle.h"


// F = K * e , where F is the force applied to the spring, k is the spring constant, and e is the extention of the spring
// length of the spring at a given moment is equal to the distance between it's two end points
// extention (e) of the spring at a given moment is equal to: currentLength - restLength

// F = -kx
class Spring
{
	
private:
	float restLength;				// the resting length of the spring in meters.
	float restLengthPixel;			// the resting length of the spring in pixels.
	
	float currentLength;			// the current length of the spring in meters.
	float currentLengthPixel;		// the current length of the spring in pixels.
	
	float extention;				// the extention of the spring in meters.
	float extentionPixel;			// the extention of the spring in pixels.
	
	float springConstant;			// the spring stiffness in N/m.
	float dampingCoefficient;		
	
	Particle* particleA;
	Particle* particleB;
	
public:
	
};


#endif
