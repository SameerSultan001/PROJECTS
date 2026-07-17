#include "physicsUtilities.h"

float ConvertPixelToMeter(float pixel)
{
	return pixel * PIXEL_TO_METER / SCALING;
}

float ConvertMeterToPixel(float meter)
{
	return meter * METER_TO_PIXEL * SCALING;
}

Vector2 FindCentroid(Vector2 pointA, Vector2 pointB, Vector2 pointC)
{
	Vector2 CenterOfMass;

	CenterOfMass.x = (pointA.x + pointB.x + pointC.x)/3.0f;
	CenterOfMass.y = (pointA.y + pointB.y + pointC.y)/3.0f;

	return CenterOfMass;
}


Vector2 FindCenterOfMass(Vector2 pointA, float massA, Vector2 pointB, float massB, Vector2 pointC, float massC)
{
	Vector2 CenterOfMass;

	float totalMass = massA + massB + massC;


	CenterOfMass.x = (pointA.x * massA + pointB.x * massB + pointC.x * massC) / totalMass;
	CenterOfMass.y = (pointA.y * massA + pointB.y * massB + pointC.y * massC) / totalMass;

	return CenterOfMass;
}