#include "pendulum.h"


// Pendulum Class ============================================================================================================

	
void Pendulum::UpdateEnergy()
{
	potentialEnergy = mass * GRAVITY * actualStringLength * (1 - cos(angle));
	kineticEnergy = 0.5f * mass * (actualStringLength * angularVelocity) * (actualStringLength * angularVelocity);
	totalEnergy = potentialEnergy + kineticEnergy;		
}

void Pendulum::SimulatePhysics(float dt)
{
	angularAcceleration = -(GRAVITY / actualStringLength) * sin(angle) - (dampingCoeffecient * angularVelocity);		
	angularVelocity += angularAcceleration * dt;
	angle += angularVelocity * dt;
	timeElapsed += dt;		
}

void Pendulum::UpdateBobPosition()
{
	Vector2 newCenter;
	
	newCenter.x = pivotCoordinate.x + (stringLength*sin(angle));
	newCenter.y = pivotCoordinate.y + (stringLength*cos(angle));
	
	circle.SetCenter(newCenter);		
}

void Pendulum::DisplayInfo() const
{
	DrawText(("Initial Angle: " + std::to_string(angleDisplaced) + " rad.").c_str(), displayCoordinate.x, displayCoordinate.y, displayFontSize, displayFontColor);
	DrawText(("String Length: " + std::to_string(actualStringLength) + " m.").c_str(), displayCoordinate.x, displayCoordinate.y + (displayFontSize), displayFontSize, displayFontColor);
	DrawText(("Damping Coeffecient: " + std::to_string(dampingCoeffecient) + ".").c_str(), displayCoordinate.x, displayCoordinate.y + (2 * displayFontSize), displayFontSize, displayFontColor);
	DrawText(("Current Angle: " + std::to_string(angle) + " rad.").c_str(), displayCoordinate.x, displayCoordinate.y + (3 * displayFontSize), displayFontSize, displayFontColor);
	DrawText(("Potential Energy: " + std::to_string(potentialEnergy) + " J.").c_str(), displayCoordinate.x, displayCoordinate.y + (4 * displayFontSize), displayFontSize, displayFontColor);
	DrawText(("Kinetic Energy: " + std::to_string(kineticEnergy) + " J.").c_str(), displayCoordinate.x, displayCoordinate.y + (5 * displayFontSize), displayFontSize, displayFontColor);
	DrawText(("Total Energy: " + std::to_string(totalEnergy) + " J.").c_str(), displayCoordinate.x, displayCoordinate.y + (6 * displayFontSize), displayFontSize, displayFontColor);
}


// Constructors ==============================================================================================================

Pendulum::Pendulum(Vector2 pivotCoordinate, float actualStringLength) : bobRadius(25.0f), bobColor(RED), circle({SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, bobRadius, bobColor), pivotCoordinate(pivotCoordinate)
{
	angularAcceleration = 0.0f;
	angularVelocity = 0.0f;
		
	angle = 0.0f;
	angleDisplaced = 0.0f;
	
	dampingCoeffecient = 0.0f; 		
	
	potentialEnergy = 0.0f;
	kineticEnergy = 0.0f;
	totalEnergy = 0.0f;
				
	timeElapsed = 0.0f;
	
	this->actualStringLength = actualStringLength;
	stringLength = ConvertMeterToPixel(actualStringLength);
	stringThickness = 5.0f;
	stringColor = WHITE;
	
	mass = 1.0f;	

	dragging = false;
	pause = false;
	displayStatus = true;
	
	displayCoordinate = {0, SCREEN_HEIGHT/2};
	displayFontSize = 20.0f;
	displayFontColor = GREEN;
}

// Setters ===================================================================================================================

void Pendulum::SetDisplayStatus(bool status)
{
	displayStatus = status;
}

void Pendulum::SetDisplayInfo(Vector2 coordinate, float fontSize, Color color)
{
	displayCoordinate = coordinate;
	displayFontSize = fontSize;
	displayFontColor = color;
}

void Pendulum::SetPivotCoordinate(Vector2 newPivotCoordinate)
{
	pivotCoordinate = newPivotCoordinate;
}

void Pendulum::SetBobInfo(float newRadius, Color newColor)
{
	bobRadius = newRadius;
	bobColor = newColor;
	circle.SetRadius(newRadius);
	circle.SetColor(newColor);
}

void Pendulum::SetMass(float newMass)
{
	mass = newMass;
}

void Pendulum::SetDampingCoeffecient(float newDampingCoeffecient)
{
	dampingCoeffecient = newDampingCoeffecient;
}


// Getters ===================================================================================================================

Vector2 Pendulum::GetBobCenter() const
{
	return circle.GetCenter();
}


// Base Functions ============================================================================================================

// Input:
void Pendulum::Input(const InputManager& input)
{
	if(input.IsKeyPressed(KEY_SPACE))
	{
		pause = !pause;
	}
	if(DetectCircleCollisionWithVec2(circle, input.GetMousePosition()) && input.IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		dragging = true;
		dragOffset = input.GetMousePosition() - circle.GetCenter();
	}
	if(input.IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
	{
		dragging = false;
	}
	if(dragging)
	{
		circle.SetCenter(input.GetMousePosition() - dragOffset);
		
		float dx = circle.GetCenter().x - pivotCoordinate.x;
		float dy = circle.GetCenter().y - pivotCoordinate.y;
		
		angleDisplaced = atan2(dx, dy);
		
		timeElapsed = 0.0f;
		
		stringLength = Vector2Distance(pivotCoordinate, circle.GetCenter());
		actualStringLength = ConvertPixelToMeter(stringLength);
		
		angle = angleDisplaced;
		angularVelocity = 0.0;
		
		if(displayStatus)
		{
			UpdateEnergy();
		}
	}				
}


// Update:
void Pendulum::Update(float dt)
{	
	if(dragging) { return; }	// donot update anything while dragging
	if(pause) { return; }		// donot update anything while paused
	
	SimulatePhysics(dt);		
	UpdateBobPosition();
	
	if(displayStatus)
	{
		UpdateEnergy();
	}		
}


// Draw:
void Pendulum::Draw() const
{
	DrawLineEx(pivotCoordinate, circle.GetCenter(), stringThickness, stringColor); 
	
	circle.Draw();		// the bob
	
	if(displayStatus)
	{
		DisplayInfo();
	}
}
