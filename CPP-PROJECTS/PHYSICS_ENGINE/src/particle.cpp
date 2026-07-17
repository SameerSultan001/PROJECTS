#include "particle.h"




Particle::Particle()
{
    position = {0,0};

    velocity = {0,0};

    acceleration = {0,0};

    accumulatedForce = {0,0};

    mass = 1.0f;								// in kg.
	
	radius = 0.05f;								// 0.05 meters = 5 cm is the actual radius.
	radiusPixel = ConvertMeterToPixel(radius);	// 0.5 cm on screen.
	color = RED;
	
	isGravityOn = false;	
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

void Particle::ApplyGravity()
{
	ApplyForce({0, GRAVITY * mass});
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

float Particle::GetMass() const { return mass; }
float Particle::GetRadius() const { return radius; }

float Particle::GetRestitution() const { return restitution; }

Circle Particle::GetCircle() const
{
	return Circle(position, radius, color);
}


// Setters ===================================================================================================================

void Particle::SetPosition(Vector2 newPosition) { position = newPosition; }

void Particle::SetVelocity(Vector2 newVelocity) { velocity = newVelocity; }

void Particle::SetAcceleration(Vector2 newAcceleration) { acceleration = newAcceleration; }

void Particle::SetMass(float newMass) { mass = newMass; }

void Particle::SetRadius(float newRadius) 
{ 
	radius = newRadius;
	radiusPixel = ConvertMeterToPixel(newRadius);
}

void Particle::SetColor(Color newColor) { color = newColor; }

void Particle::SetRestitution(float newRestitution) { restitution = newRestitution; }

void Particle::SetGravityStatus(bool status) { isGravityOn = status; }


void Particle::ApplyForce(Vector2 forceVector) { accumulatedForce += forceVector; }



// Base Functions ============================================================================================================

// Input:
void Particle::Input(const InputManager& input)
{
	
}


// Update: Responsible for updating the physical quantities of the particle by applying the accumulated force through updating acceleration, velocity, and position.
void Particle::Update(float dt)
{
	if(isGravityOn)
	{
		ApplyGravity();
	}
	
	UpdateAcceleration();
	UpdateVelocity(dt);
	UpdatePosition(dt);
	
	ClearForces();
}


// Draw: Draws the particle as a circle of a particular radius.
void Particle::Draw() const
{
	Vector2 positionPixel;
	
	positionPixel.x = ConvertMeterToPixel(position.x);
	positionPixel.y = ConvertMeterToPixel(position.y);
	
	DrawCircleV(positionPixel, radiusPixel, color);
}






