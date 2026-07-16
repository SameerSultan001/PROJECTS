//This program aims to create a movable pendulum simulation
#include "pendulum.h"

// Compilation: g++ src/*.cpp -Iinclude -o bin/Pendulum.exe $(pkg-config --cflags --libs raylib)


// main ======================================================================================================================

int main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pendulum Simulation");
	SetTargetFPS(FPS);
    
    Vector2 pivotCoordinate = {SCREEN_WIDTH/2, 0};
    
    InputManager input;
    
    Pendulum p1(pivotCoordinate, 0.1);	// 10 cm. Since scaling = 0.1, actual displayed size on screen is 1 cm.
    
    p1.SetDisplayInfo((Vector2){15.0f, SCREEN_HEIGHT*0.2}, 20.0f, GREEN);
    
    p1.SetBobCenterCoordinate((Vector2){pivotCoordinate.x + 300.0f, SCREEN_HEIGHT/2 - 200.0f});
    
    p1.SetStringLength(0.8f);
    
    p1.SetPauseStatus(true);
    
	
	while(!WindowShouldClose())
	{
		input.Update();
    	
    	p1.Input(input);
    	
    	p1.Update(input.GetFrameTime());

    	BeginDrawing();
    	
			ClearBackground(BLACK);
	    	
	    	DrawText("Pendulum Simulation", 0, 0, 20, GREEN);
	 
	    	p1.Draw();
	
    	EndDrawing();
	}
    
    CloseWindow();  
    
    return 0;
}
