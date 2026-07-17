#include "collisionResolution.h"



void ResolveCollision(Particle& particleA, Particle& particleB)
{
	if(!DetectCollisionBetweenCircles(particleA.GetCircle(), particleB.GetCircle()))
	{
		return;
	}
	
	Vector2 particleAPosition = particleA.GetPosition();	// OA
	Vector2 particleBPosition = particleB.GetPosition();	// OB
	
	Vector2 particleAVelocity = particleA.GetVelocity();
	Vector2 particleBVelocity = particleB.GetVelocity();
	
	float particleARadius = particleA.GetRadius();
	float particleBRadius = particleB.GetRadius();
	
	float particleAMass = particleA.GetMass();
	float particleBMass = particleB.GetMass();
	
	float restitutionA = particleA.GetRestitution();
	float restitutionB = particleB.GetRestitution();
	
	// compute collision normal:
	
	Vector2 vectorFromAToB = particleBPosition - particleAPosition;		// AB = AO + OB = OB - OA
	
	if(Vector2LengthSqr(vectorFromAToB) == 0.0f)						// meaning to say that both particles occupy the same position.
	{
		return;
	}
	
	Vector2 normalAToB = Vector2Normalize(vectorFromAToB);
	
	
	// seperate overlap:
	
	float distance = Vector2Distance(particleAPosition, particleBPosition);	// the distance between the two particles
	
	float penetration = particleARadius + particleBRadius - distance;		// we need to check how far the particles are overlapping
	
	Vector2 correction = normalAToB * (penetration * 0.5f);					// from A to B
	
	
	particleA.SetPosition(particleAPosition - correction);
	particleB.SetPosition(particleBPosition + correction);

	// compute relative velocity
	
	Vector2 relativeVelocity = particleBVelocity - particleAVelocity;				// from A to B (consistent with the normal)
	float velocityAlongNormal = Vector2DotProduct(relativeVelocity, normalAToB); 	// we only want the velocity along the normal
	
	if (velocityAlongNormal > 0.0f)
	{
    	return;
	}
	
	// calculate impulse
	
	float restitution = std::min(restitutionA, restitutionB);						// a combined restitution.
	
	float impulseMagnitude = -( (1 + restitution) * (velocityAlongNormal) )/( (1.0f/particleAMass) + (1.0f/particleBMass) );	// the magnitude of impulse produced.
	
	Vector2 impulseVector = normalAToB * impulseMagnitude;
	
	// apply impulse:

	particleAVelocity -= impulseVector / particleAMass;
	particleBVelocity += impulseVector / particleBMass;
	
	particleA.SetVelocity(particleAVelocity);
	particleB.SetVelocity(particleBVelocity);

}




