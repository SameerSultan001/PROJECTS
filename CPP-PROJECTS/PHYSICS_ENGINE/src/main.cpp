#include <vector>
#include "raylib.h"

#include "particle.h"
#include "collisionResolution.h"
#include "constants.h"
#include "inputManager.h"
#include "spring.h"
#include "physicsUtilities.h"

// Compilation: g++ src/*.cpp -Iinclude -o bin/Particle_Collision.exe $(pkg-config --cflags --libs raylib)

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle Collision Test");
    SetTargetFPS(FPS);

    InputManager input;

    bool pause = true;

    Particle particleA;
    Particle particleB;
    Particle particleC;

    Spring spring;
    Spring spring2;
    Spring spring3;

    spring.SetParticles(&particleA, &particleB);
    spring.SetRestLength(1.2f);
    spring.SetSpringConstant(10000.0f);

    spring2.SetParticles(&particleB, &particleC);
    spring2.SetRestLength(1.6f);
    spring2.SetSpringConstant(10000.0f);

    spring3.SetParticles(&particleC, &particleA);
    spring3.SetRestLength(2.0f);
    spring3.SetSpringConstant(10000.0f);

    //spring.SetTensionOnlySpring(true);
    //spring2.SetTensionOnlySpring(true);
    //spring3.SetTensionOnlySpring(true);

    //-------------------------
    // Particle A
    //-------------------------

    particleA.SetPosition({0.1f, 0.1f});
    particleA.SetVelocity({0.1f, 0.0f});

    particleA.SetMass(4.0f);
    particleA.SetRadius(0.03f);

    particleA.SetColor(RED);
    particleA.SetRestitution(1.0f);


    //-------------------------
    // Particle B
    //-------------------------

    particleB.SetPosition({0.1f, 1.3f});
    //particleB.SetVelocity({-0.25f, 0.00f});

    particleB.SetMass(4.0f);
    particleB.SetRadius(0.03f);

    particleB.SetColor(BLUE);
    particleB.SetRestitution(1.0f);


    //-------------------------
    // Particle C
    //-------------------------

    particleC.SetPosition({1.7f, 1.3f});

    particleC.SetMass(4.0f);
    particleC.SetRadius(0.03f);

    particleC.SetColor(YELLOW);
    particleC.SetRestitution(1.0f);


    Vector2 centerOfMass = FindCenterOfMass(particleA.GetPosition(), particleA.GetMass(), particleB.GetPosition(), particleB.GetMass(), particleC.GetPosition(), particleC.GetMass());
    Vector2 centerOfMassPixel = {ConvertMeterToPixel(centerOfMass.x), ConvertMeterToPixel(centerOfMass.y)};

    std::vector<Vector2> centerHistory;

    centerHistory.push_back(centerOfMass);

    while (!WindowShouldClose())
    {
        input.Update();

        float dt = input.GetFrameTime();

        if(input.IsKeyPressed(KEY_SPACE))
        {
            pause = !pause;
        }

        //----------------------------------
        // Physics
        //----------------------------------

        const int substeps = 16;
        float subDt = dt / substeps;
        
        if(!pause)
        {
            for(int i = 0; i < substeps; i++)
            {
                spring.Update(subDt);
                spring2.Update(subDt);
                spring3.Update(subDt);
                particleA.Update(subDt);
                particleB.Update(subDt);
                particleC.Update(subDt);
                ResolveCollision(particleA, particleB);
                ResolveCollision(particleA, particleC);
                ResolveCollision(particleB, particleC);
            }

            centerOfMass = FindCenterOfMass(particleA.GetPosition(), particleA.GetMass(), particleB.GetPosition(), particleB.GetMass(), particleC.GetPosition(), particleC.GetMass());

            centerOfMassPixel.x = ConvertMeterToPixel(centerOfMass.x);
            centerOfMassPixel.y = ConvertMeterToPixel(centerOfMass.y);

            centerHistory.push_back(centerOfMass);           
        }
        //----------------------------------
        // Drawing
        //----------------------------------

        BeginDrawing();

        ClearBackground(BLACK);

        spring.Draw();
        spring2.Draw();
        spring3.Draw();
        particleA.Draw();
        particleB.Draw();
        particleC.Draw();

        for(int i = 0; i < centerHistory.size(); i++)
        {
            Vector2 centerHistoryPixel = {ConvertMeterToPixel(centerHistory[i].x), ConvertMeterToPixel(centerHistory[i].y)};
            DrawCircleV(centerHistoryPixel, 2.0f, ORANGE);
        }

        DrawCircleV(centerOfMassPixel, 5.0f, GREEN);

        DrawFPS(20,20);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}