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

float Spring::GetRestLength() const
{
	return restLength;
}

float Spring::GetCurrentLength() const
{
	return currentLength;
}

float Spring::GetExtension() const
{
	return extension;
}

float Spring::GetMaxLength() const
{
	return maxLength;
}

float Spring::GetSpringConstant() const
{
	return springConstant;
}

float Spring::GetDampingCoefficient() const
{
	return dampingCoefficient;
}

float Spring::GetForceOfString() const
{
	return forceOfSpring;
}

Vector2 Spring::GetEndACoordinate() const
{
	return endACoordinate;
}

Vector2 Spring::GetEndBCoordinate() const
{
	return endBCoordinate;
}

Vector2 Spring::GetForceOnParticleA() const
{
	return forceOnParticleA;
}

Vector2 Spring::GetForceOnParticleB() const
{
	return forceOnParticleB;
}

Vector2 Spring::GetVectorFromAToB() const
{
	return vectorFromAToB;
}

Vector2 Spring::GetVectorFromBToA() const
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
	
	particleAPixel.x = ConvertMeterToPixel(particleA->GetPosition().x);
	particleAPixel.y = ConvertMeterToPixel(particleA->GetPosition().y);
	
	particleBPixel.x = ConvertMeterToPixel(particleB->GetPosition().x);
	particleBPixel.y = ConvertMeterToPixel(particleB->GetPosition().y);
	
	
	DrawLineEx(particleAPixel, particleBPixel, 4.0f, WHITE);
}
