#include "particle.h"




Particle::Particle()
{
    position = {0,0};

    velocity = {0,0};

    acceleration = {0,0};

    accumulatedForce = {0,0};

    mass = 1.0f;
	
	radius = 0.05f;		// 5 cm is the actual radius. 0.5 cm on screen.
	radiusPixel = ConvertMeterToPixel(radius);
}

// Helper Functions ==========================================================================================================


void Particle::UpdateAcceleration()
{
	acceleration = accumulatedForce / mass;	
}

void Particle::UpdateVelocity(float dt)
{
	velocity += acceleration * dt;
}

void Particle::UpdatePosition(float dt)
{
	position += velocity * dt;
}

void Particle::ClearForces()
{
	accumulatedForce = {0,0};
}

// Getters ===================================================================================================================

Vector2 Particle::GetPosition() const { return position; }
Vector2 Particle::GetVelocity() const { return velocity; }
Vector2 Particle::GetAcceleration() const { return acceleration; }
Vector2 Particle::GetAccumulatedForce() const { return accumulatedForce; }


// Setters ===================================================================================================================

void Particle::SetPosition(Vector2 newPosition) { position = newPosition; }

void Particle::SetVelocity(Vector2 newVelocity) { velocity = newVelocity; }

void Particle::SetAcceleration(Vector2 newAcceleration) { acceleration = newAcceleration; }

void Particle::ApplyForce(Vector2 force) { accumulatedForce += force; }



// Base Functions ============================================================================================================


void Particle::Input(const InputManager& input)
{
	
}


void Particle::Update(float dt)
{
	UpdateAcceleration();
	UpdateVelocity(dt);
	UpdatePosition(dt);
	ClearForces();
}

void Particle::Draw() const
{
	Vector2 positionPixel;
	
	positionPixel.x = ConvertMeterToPixel(position.x);
	positionPixel.y = ConvertMeterToPixel(position.y);
	
	DrawCircleV(positionPixel, radiusPixel, RED);
}






