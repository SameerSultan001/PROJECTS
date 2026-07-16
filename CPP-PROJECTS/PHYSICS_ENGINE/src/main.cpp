#include "raylib.h"

#include "particle.h"
#include "spring.h"
#include "inputManager.h"

// Compilation: g++ src/*.cpp -Iinclude -o bin/Mass_Spring_System.exe $(pkg-config --cflags --libs raylib)


// main ======================================================================================================================

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mass Spring System");

    SetTargetFPS(FPS);

	InputManager input;
	
    Particle particleA;
    Particle particleB;
    //Particle particleC;

    particleA.SetPosition({ConvertPixelToMeter(0.2*SCREEN_WIDTH), ConvertPixelToMeter(SCREEN_HEIGHT/2)});
    particleB.SetPosition({ConvertPixelToMeter(0.8*SCREEN_WIDTH), ConvertPixelToMeter(SCREEN_HEIGHT/2)});
    //particleC.SetPosition({ConvertPixelToMeter(550), ConvertPixelToMeter(250)});

    Spring spring;
    //Spring spring1;

    spring.SetParticles(&particleA,&particleB);
    //spring1.SetParticles(&particleB, &particleC);

    spring.SetRestLength(ConvertPixelToMeter(0.55*SCREEN_WIDTH));      // choose whatever looks good
    spring.SetSpringConstant(50.0f);
    
    //spring1.SetRestLength(0.03f);
    //spring1.SetSpringConstant(50.0f);
    
    bool pause = false;

    while(!WindowShouldClose())
    {
    	input.Update();
    	
        float dt = input.GetFrameTime();
        
		if(input.IsKeyPressed(KEY_SPACE))
		{
			pause = !pause;
		}
		
		if(!pause)
		{
	        spring.Update(dt);
	        //spring1.Update(dt);
	
	        particleA.Update(dt);
	        particleB.Update(dt);
	        //particleC.Update(dt);
		}
        BeginDrawing();

        ClearBackground(BLACK);

        spring.Draw();
        //spring1.Draw();

        particleA.Draw();
        particleB.Draw();
        //particleC.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
