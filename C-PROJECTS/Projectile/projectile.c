#include <stdio.h>
#include "raylib.h"
#include <math.h>

#define WIDTH 900
#define HEIGHT 600
#define FPS 120

#define GROUND_Y (0.9*HEIGHT) //90 percent the height from the top
#define GROUND_THICKNESS 2

#define RADIUS 10


#define GRAVITY 9.80665





int main(void) {
	
	
	float V;
	printf("Enter Velocity: ");
	scanf("%f", &V);
	
	float angle;
	printf("Enter Angle (Degrees): ");
	scanf("%f", &angle);
	angle = (angle/180)*3.14159264;
	
	float timeScale;
	printf("Enter Time Scaling Factor: ");
	scanf("%f", &timeScale);
	
	
	InitWindow(WIDTH, HEIGHT, "Projectile Motion");
    SetTargetFPS(FPS);
 
    Vector2 groundStartPos = {0, GROUND_Y};
    Vector2 groundEndPos = {WIDTH, GROUND_Y};     
	
	float dt = 0;
	float t = 0; //t represents the time since the start of the simulation (from when the program is run)
	
	float x = 0 + RADIUS, y = 0 + RADIUS; //coordinates of the ball (red circle) initialized to be at the top left of the screen
	
	float v = V * 10; //to convert from pixels to kinda real life stuff for simulation realism and accuracy
	
	
	
	
	while(!WindowShouldClose())
	{
    	BeginDrawing();
    	ClearBackground(BLACK);
    	DrawText("Projectile Motion Simulation", 0, GROUND_Y, 20, GREEN);
    	
    	dt = GetFrameTime();
    	
    	DrawLineEx(groundStartPos, groundEndPos, GROUND_THICKNESS, GRAY); //the line at the ground (representing the ground)

		
		x = v * cos(angle) * t + RADIUS;
		y = -(v*sin(angle)*t - 0.5*GRAVITY*t*t) + (GROUND_Y - RADIUS);
		
		if(y >= GROUND_Y - RADIUS){
			t = 0;
			y = GROUND_Y - RADIUS;
		}
		
		DrawCircle(x, y, RADIUS, RED);
    	
    	t += (dt*timeScale);
    	
    	EndDrawing();
	}
    
    CloseWindow();  
    
}
