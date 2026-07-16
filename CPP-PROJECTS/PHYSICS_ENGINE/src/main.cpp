#include "raylib.h"

#include "particle.h"
#include "spring.h"

// Compilation: g++ src/*.cpp -Iinclude -o bin/Mass_Spring_System.exe $(pkg-config --cflags --libs raylib)


// main ======================================================================================================================

int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Mass Spring");

    SetTargetFPS(120);

    Particle particleA;
    Particle particleB;

    particleA.SetPosition({400,400});
    particleB.SetPosition({700,400});

    Spring spring;

    spring.SetParticles(&particleA,&particleB);

    spring.SetRestLength(0.03f);      // choose whatever looks good
    spring.SetSpringConstant(50.0f);

    while(!WindowShouldClose())
    {
        float dt = GetFrameTime();

        spring.Update(dt);

        particleA.Update(dt);
        particleB.Update(dt);

        BeginDrawing();

        ClearBackground(BLACK);

        spring.Draw();

        particleA.Draw();
        particleB.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
