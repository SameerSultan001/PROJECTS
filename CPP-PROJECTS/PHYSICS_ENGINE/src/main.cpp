#include <string>

#include "raylib.h"

#include "particle.h"
#include "spring.h"
#include "inputManager.h"

// Compilation: g++ src/*.cpp -Iinclude -o bin/Mass_Spring_System.exe $(pkg-config --cflags --libs raylib)


// main ======================================================================================================================

/*
int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mass Spring System");

    SetTargetFPS(FPS);

	InputManager input;
	
    Particle particleA;
    Particle particleB;
    Particle particleC;

    particleA.SetPosition({ConvertPixelToMeter(0.3*SCREEN_WIDTH), ConvertPixelToMeter(SCREEN_HEIGHT*0.7)});
    particleB.SetPosition({ConvertPixelToMeter(0.7*SCREEN_WIDTH), ConvertPixelToMeter(SCREEN_HEIGHT*0.7)});
    particleC.SetPosition({ConvertPixelToMeter(SCREEN_WIDTH/2), ConvertPixelToMeter(SCREEN_HEIGHT*0.3)});

    Spring spring;
    Spring spring1;

    spring.SetParticles(&particleA,&particleB);
    spring1.SetParticles(&particleB, &particleC);

    spring.SetRestLength(ConvertPixelToMeter(0.3*SCREEN_WIDTH));      // choose whatever looks good
    spring.SetSpringConstant(50.0f);
    
    spring1.SetRestLength(ConvertPixelToMeter(0.3*SCREEN_WIDTH));
    spring1.SetSpringConstant(50.0f);
    
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
	        spring1.Update(dt);
	
	        particleA.Update(dt);
	        particleB.Update(dt);
	        particleC.Update(dt);
		}
        BeginDrawing();

        ClearBackground(BLACK);

        spring.Draw();
        spring1.Draw();

        particleA.Draw();
        particleB.Draw();
        particleC.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
*/

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mass Spring System");

    SetTargetFPS(FPS);

	InputManager input;
	
    Particle particleA;
    Particle particleB;
    Particle particleC;

    particleA.SetPosition({ConvertPixelToMeter(0.5*SCREEN_WIDTH), ConvertPixelToMeter(SCREEN_HEIGHT*0.1)});
    particleB.SetPosition({ConvertPixelToMeter(0.5*SCREEN_WIDTH), 0.6f});

	particleA.SetMass(10000000.0f); // to simulate an almost immovable object, like a ceiling probably.
	particleB.SetMass(1.0f);
	
	particleB.SetGravityStatus(true);
	
    Spring spring;

    spring.SetParticles(&particleA,&particleB);

    spring.SetRestLength(0.5);      // choose whatever looks good
    spring.SetSpringConstant(50.0f);
    
    
    bool pause = true;

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
	
	        particleA.Update(dt);
	        particleB.Update(dt);
		}
        BeginDrawing();

        ClearBackground(BLACK);

        spring.Draw();
        

        particleA.Draw();
        particleB.Draw();
        
        DrawText(("Current Length: " + std::to_string(spring.GetCurrentLength()) + " m.").c_str() , 0,0,20, GREEN);
        
        DrawText(("Extension: " + std::to_string(spring.GetExtension()) + " m.").c_str() , 0,20,20, GREEN);
        
        DrawText(("Force Of Spring: " + std::to_string(spring.GetForceOfString()) + " N.").c_str() , 0,40,20, GREEN);
        
        DrawText(("Velocity.y: " + std::to_string(particleB.GetVelocity().y) + " m/s.").c_str() , 0,60,20, GREEN);
        
        DrawText(("Acceleration.y: " + std::to_string(particleB.GetVelocity().y) + " m/s2.").c_str() , 0,80,20, GREEN);
        

        EndDrawing();
    }

    CloseWindow();

    return 0;	
}
