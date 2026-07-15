#ifndef PENDULUM_H
#define PENDULUM_H

#include <cmath>
#include <string>

#include "raylib.h"
#include "raymath.h"

#include "inputManager.h"
#include "circle.h"
#include "physicsUtilities.h"
#include "collisionDetection.h"
#include "constants.h"

// Pendulum Class ============================================================================================================

class Pendulum
{
	
private:
	Vector2 pivotCoordinate;			// the point where the string is attached to the ceiling.
	
	float bobRadius;
	Color bobColor;
	
	Circle circle;						// representing the pendulum bob.
	
	
	float angularAcceleration;			// how fast the angular velocity changes with respect to time.
	float angularVelocity;				// how fast the angle of the pendulum, with the vertical, changes with respect to time.
		
	float angle;						// of the string, with the vertical, in radians.
	float angleDisplaced;				// angle that the string makes after it has been dragged to a certain point (initial angle).
	
	float mass;							// in kg.
	
	float dampingCoeffecient; 			// how much resistance the pendulum faces in its motion.
	
	float potentialEnergy;
	float kineticEnergy;
	float totalEnergy;					// K.E + P.E
		
	float timeElapsed;					// total time since the pendulum has been released from initial position.
	
	
	
	float stringLength;					// this is the length of the string in term of pixels.
	float actualStringLength;			// this is in terms of meters.
	float stringThickness;				// this is in terms of pixels.
	Color stringColor;
	
	Vector2 dragOffset;					// used when dragging the pendulum, since we won't always grab it from its center.
		
	bool dragging;						// to check if the user wants to drag the pendulum.
	bool pause;							// to stop the pendulum.
	bool displayStatus;					// to check if the user want to display information about the pendulum.
	
	Vector2 displayCoordinate;			// top left corner of the display information box.
	float displayFontSize;				// size of the font to be displayed (in pixels).
	Color displayFontColor;				// color of the text that would need to be displayed.
	
	
	
	void UpdateEnergy();
	
	void SimulatePhysics(float dt);
	
	void UpdateBobPosition();
	
	void DisplayInfo() const;
	
	
public:
	Pendulum(Vector2 pivotCoordinate, float stringLength);
	
	// Setters ===============================================================================================================
	
	void SetDisplayStatus(bool status);
	
	void SetDisplayInfo(Vector2 coordinate, float fontSize, Color color);
	
	void SetPivotCoordinate(Vector2 newPivotCoordinate);
	
	void SetBobInfo(float newRadius, Color newColor);
	
	void SetMass(float newMass);
	
	void SetDampingCoeffecient(float newDampingCoeffecient);

	
	// Getters ===============================================================================================================
	
	Vector2 GetBobCenter() const;
	
	
	// Base Functions ========================================================================================================
	
	// Inputs:
	void Input(const InputManager& input);
	
	
	// Updates:
	void Update(float dt);
	
	
	// Draws:
	void Draw() const;
};

#endif
