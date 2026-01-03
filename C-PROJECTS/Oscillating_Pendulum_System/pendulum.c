#include "raylib.h"
#include <stdio.h>
#include <math.h>


#define WIDTH 900
#define HEIGHT 600
#define FPS 120

#define CEILING_Y (0.1*HEIGHT)
#define CEILING_THICKNESS 5

#define STRING_LENGTH 450
#define STRING_THICKNESS 3

#define RADIUS 25
#define AMPLITUDE 0.43 //acts as max angle (in radians)

#define PIXELS_PER_METER 300.0f
#define GRAVITY (9.81f * PIXELS_PER_METER)
#define DAMPING 0.05f


int main(void) {
    InitWindow(WIDTH, HEIGHT, "raylib test");
    SetTargetFPS(FPS);
    
    Vector2 ceilingStartPos = {0, CEILING_Y};
    Vector2 ceilingEndPos = {WIDTH, CEILING_Y};    
    
    
    Vector2 stringStartPos = {WIDTH/2, CEILING_Y}; //just initialization stuff
    Vector2 stringEndPos = {WIDTH/2, CEILING_Y + STRING_LENGTH}; //just initialization stuff
    
    float x = 0, y = 0;
    
    float period = 2*3.141592654*sqrt(STRING_LENGTH/9.80665); //probably useless
    float angularFreq = sqrt(GRAVITY/STRING_LENGTH); 
    
    float dt = 0;
    float t = 0;
    
    float currentAngle = 0;
    float decayedAmplitude = 0; //initialized to zero 0, just bcz it's more effecient
    
    while(!WindowShouldClose())
	{
    	BeginDrawing();
    	ClearBackground(BLACK);
    	DrawText("raylib works!", 200, 200, 20, GREEN);
    	
    	dt = GetFrameTime();
    	
    	DrawLineEx(ceilingStartPos, ceilingEndPos, CEILING_THICKNESS, GRAY); //the line at the ceiling
    	
    	decayedAmplitude = AMPLITUDE * exp(-DAMPING * t);
    	
    	currentAngle = decayedAmplitude*cos(angularFreq*t);
    	
    	if (decayedAmplitude < 0.001) {
    		currentAngle = 0; 
		}
    	
    	x = (STRING_LENGTH+RADIUS)*sin(currentAngle) + WIDTH/2;
    	y = (STRING_LENGTH+RADIUS)*cos(currentAngle) + CEILING_Y;
    	DrawCircle(x, y, RADIUS, RED); 
    	
    	stringEndPos = (Vector2){STRING_LENGTH * sin(currentAngle) + (WIDTH/2), STRING_LENGTH * cos(currentAngle) + CEILING_Y};
    	DrawLineEx(stringStartPos, stringEndPos, STRING_THICKNESS, GRAY);
    	
    	t += dt;
    	EndDrawing();
	}
    
    CloseWindow();
    return 0;
}
