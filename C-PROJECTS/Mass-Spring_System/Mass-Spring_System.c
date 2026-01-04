#include <stdio.h>
#include "raylib.h"
#include <math.h>

#define WIDTH 900
#define HEIGHT 600
#define REC_LENGTH 100
#define GROUND_Y (HEIGHT*0.6)
#define GROUND_THICKNESS 5
#define FPS 120

#define NUM_SPRING_ELEMENTS 40
#define SPRING_ELEMENT_LENGTH 50
#define SPRING_ELEMENT_THICKNESS 3

#define AMPLITUDE 180
#define PERIOD 0.8 //seconds to complete one full cycle
#define DAMPING_COEFFECIENT 0.2


int main(void)
{
    InitWindow(WIDTH, HEIGHT, "raylib MSYS2");
    SetTargetFPS(FPS);

    float x = 0,y = 0; //coordinates of the rectangle (top left corner)
    
    y = GROUND_Y - GROUND_THICKNESS/2 - REC_LENGTH;
    
    Vector2 groundStartPos = {0,GROUND_Y};
    Vector2 groundEndPos = {WIDTH, GROUND_Y};
    
    float velocity = 60.0; //60 pixel per second
    
    Vector2 springElementStartPos = {0, GROUND_Y};
    Vector2 springElementEndPos = {0, GROUND_Y}; //initialized to just this
    
    float dt = 0;
    float t = 0;
    
    float angularFreq = (2*3.14159)/PERIOD;
    float initial_X = 300;
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("raylib works!", 200, 200, 20, GREEN);
        
        DrawLineEx(groundStartPos, groundEndPos, GROUND_THICKNESS, GRAY);
        
        dt = GetFrameTime();
        
        
        //x += velocity*dt;
        
        x = exp(-DAMPING_COEFFECIENT*t)*AMPLITUDE*cos(angularFreq*t) + initial_X;
        
        if(exp(-DAMPING_COEFFECIENT*t)*AMPLITUDE <= 1){
        	x = initial_X;
		}
        
        DrawRectangle(x, y, REC_LENGTH, REC_LENGTH, RED);
        
        
        float dx = x/NUM_SPRING_ELEMENTS; //dx is horizontal distance between consequitive spring elements
        int i;
        for(i = 0; i < NUM_SPRING_ELEMENTS; i++) //this for loop is just for the spring elements, based on the x position of the rectangle
		{
        	if(i%2 == 0){ //for spring elements that look like "/"
        		springElementStartPos = (Vector2){i*dx, GROUND_Y - REC_LENGTH/2 + SPRING_ELEMENT_LENGTH/2}; //start for these is always the ground
        		springElementEndPos = (Vector2){(i+1)*dx, GROUND_Y - sqrt( pow(SPRING_ELEMENT_LENGTH,2) - pow(dx,2) ) - REC_LENGTH/2 + SPRING_ELEMENT_LENGTH/2};	
			}
			else{ //for spring elements that look like "\"
        		springElementStartPos = (Vector2){i*dx, GROUND_Y - sqrt( pow(SPRING_ELEMENT_LENGTH,2) - pow(dx,2) ) - REC_LENGTH/2 + SPRING_ELEMENT_LENGTH/2};
        		springElementEndPos = (Vector2){(i+1)*dx, GROUND_Y - REC_LENGTH/2 + SPRING_ELEMENT_LENGTH/2}; //end for these is always the ground			
			}
			DrawLineEx(springElementStartPos, springElementEndPos, SPRING_ELEMENT_THICKNESS, GRAY);
		}
        
        t+= dt;
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
