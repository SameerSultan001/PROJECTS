#include "spring.h"


Spring::Spring()
{
    particleA = nullptr;
    particleB = nullptr;

    springConstant = 15.0f;

    dampingCoefficient = 0.0f;

    restLength = 1.0f;		// this is 1 meter. size on screen should be 10 cm.	
}

// Helper Functions ==========================================================================================================


void Spring::UpdateEndPoints()
{
	endACoordinate = particleA->GetPosition();
	endBCoordinate = particleB->GetPosition();
}

void Spring::UpdateEndPointVectors()
{
	vectorFromAToB = endBCoordinate - endACoordinate; // AB = AO + OB = OB - OA
	vectorFromBToA = Vector2Negate(vectorFromAToB);	// BA = -AB
}

void Spring::UpdateCurrentLength()
{
	currentLength = Vector2Distance(endACoordinate, endBCoordinate);
	//currentLengthPixel = ConvertMeterToPixel(currentLength);
}

void Spring::UpdateExtension()
{
	extension = currentLength - restLength;
}

void Spring::UpdateForceOfSpring()
{
	forceOfSpring = springConstant * extension;
}

void Spring::UpdateForceOnParticles()
{
	forceOnParticleA = Vector2Normalize(vectorFromAToB) * forceOfSpring;
	forceOnParticleB = Vector2Negate(forceOnParticleA);
}

void Spring::ApplyForceOnParticles()
{
	particleA->ApplyForce(forceOnParticleA);
	particleB->ApplyForce(forceOnParticleB);
}


// Getters ===================================================================================================================

float GetRestLength() const
{
	return restLength;
}

float GetCurrentLength() const
{
	return currentLength;
}

float GetExtension() const
{
	return extension;
}

float GetMaxLength() const
{
	return maxLength;
}

float GetSpringConstant() const
{
	return springConstant;
}

float GetDampingCoefficient() const
{
	return dampingCoefficient;
}

float GetForceOfString() const
{
	return forceOfString;
}

Vector2 GetEndACoordinate() const
{
	return endACoordinate;
}

Vector2 GetEndBCoordinate() const
{
	return endBCoordinate;
}

Vector2 GetForceOnParticleA() const
{
	return forceOnParticleA;
}

Vector2 GetForceOnParticleB() const
{
	return forceOnParticleB;
}

Vector2 GetVectorFromAToB() const
{
	return vectorFromAToB;
}

Vector2 GetVectorFromBToA() const
{
	return vectorFromBToA;
}


// Setters ===================================================================================================================

void Spring::SetParticles(Particle* newParticleA, Particle* newParticleB)
{
	particleA = newParticleA;
	particleB = newParticleB;
}

void Spring::SetParticleA(Particle* newParticleA)
{
	particleA = newParticleA;
}

void Spring::SetParticleB(Particle* newParticleB)
{
	particleB = newParticleB;
}

void Spring::SetRestLength(float newRestLength)
{
    restLength = newRestLength;
}

void Spring::SetSpringConstant(float newSpringConstant)
{
    springConstant = newSpringConstant;
}

void Spring::SetDampingCoefficient(float newDampingCoefficient)
{
    dampingCoefficient = newDampingCoefficient;
}

// Base Functions ============================================================================================================

void Spring::Update(float dt)
{
	UpdateEndPoints();
	UpdateEndPointVectors();
	UpdateCurrentLength();
	UpdateExtension();
	UpdateForceOfSpring();
	UpdateForceOnParticles();
	ApplyForceOnParticles();
	
}


void Spring::Draw() const
{
	Vector2 particleAPixel;
	Vector2 particleBPixel;
	
	particleAPixel.x = ConvertMeterToPixel(endACoordinate.x);
	particleAPixel.y = ConvertMeterToPixel(endACoordinate.y);
	
	particleBPixel.x = ConvertMeterToPixel(endBCoordinate.x);
	particleBPixel.y = ConvertMeterToPixel(endBCoordinate.y);
	
	
	DrawLineEx(particleAPixel, particleBPixel, 4.0f, WHITE);
}
