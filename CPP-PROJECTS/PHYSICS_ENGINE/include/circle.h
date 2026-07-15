#ifndef CIRCLE_H
#define CIRCLE_H

#include "raylib.h"


class Circle
{
	
private:
	float radius;
	Vector2 center;
	Color color;
	
public:	
	Circle(Vector2 center, float radius, Color color);
	
	// Getters:	
	Vector2 GetCenter() const;		
	float GetRadius() const;
	
	// Setters:	
	void SetCenter(Vector2 newCenter);	
	void SetRadius(float newRadius);	
	void SetColor(Color newColor);
	
	// Updates:	
	void Move(Vector2 delta);
	
	// Draws:	
	void Draw() const;
};

#endif
