#ifndef PHYSICS_UTILITIES_H
#define PHYSICS_UTILITIES_H

#include "constants.h"
#include "raymath.h"

float ConvertPixelToMeter(float pixel);

float ConvertMeterToPixel(float meter);

Vector2 FindCentroid(Vector2 pointA, Vector2 pointB, Vector2 pointC);

Vector2 FindCenterOfMass(Vector2 pointA, float massA, Vector2 pointB, float massB, Vector2 pointC, float massC);

#endif
