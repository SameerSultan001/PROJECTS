#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "circle.h"

bool DetectCircleCollisionWithVec2(const Circle& circle, Vector2 vec2);

bool DetectCollisionBetweenCircles(const Circle& circle1, const Circle& circle2);

#endif
