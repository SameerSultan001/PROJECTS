#include "collisionDetection.h"

bool DetectCircleCollisionWithVec2(const Circle& circle, Vector2 vec2)
{
	Vector2 center = circle.GetCenter();	
	float radius = circle.GetRadius();
	
	return ((center.x - vec2.x)*(center.x - vec2.x)) + (center.y - vec2.y)*(center.y - vec2.y) <= (radius*radius);
}


bool DetectCollisionBetweenCircles(const Circle& circle1, const Circle& circle2)
{
	float dx = circle1.GetCenter().x - circle2.GetCenter().x;
	float dy = circle1.GetCenter().y - circle2.GetCenter().y;
	
	float radiusSum = circle1.GetRadius() + circle2.GetRadius();
	
	return ( (dx * dx) + (dy * dy) ) <= (radiusSum * radiusSum);
}
