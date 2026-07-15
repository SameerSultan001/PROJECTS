#include "circle.h"



// Constructors:
Circle::Circle(Vector2 center, float radius, Color color) : center(center), radius(radius), color(color) {}

// Getters:
Vector2 Circle::GetCenter() const { return center; }	

float Circle::GetRadius() const { return radius; }

// Setters:
void Circle::SetCenter(Vector2 newCenter) { center = newCenter; }

void Circle::SetRadius(float newRadius) { radius = newRadius; }

void Circle::SetColor(Color newColor) { color = newColor; }

// Updates:
void Circle::Move(Vector2 delta)
{
	center.x += delta.x;
	center.y += delta.y;
}

// Draws:
void Circle::Draw() const
{
	DrawCircle(center.x, center.y, radius, color);
}

