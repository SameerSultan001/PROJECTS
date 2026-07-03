#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include "raylib.h"

using namespace std;
// Compilation: g++ flappy_bird.cpp -o flappy_bird $(pkg-config --cflags --libs raylib)

#define WIDTH 1920
#define HEIGHT 980
#define FPS 30

#define GRAVITY 1800.0


struct RectCoordinates
{
	Vector2 topLeft;
	Vector2 topRight;
	Vector2 bottomLeft;
	Vector2 bottomRight;
};



bool CheckCollisionRecsZ(RectCoordinates rect1, RectCoordinates rect2)
{
	
}




// ============================================================================================================================

class Bird	// represented by a rectangle
{
private:
	float length;
	float width;
	
	double velocity;
	
	Vector2 coordinate;	// top left corner of the rectangle
	Sound jumpSound;
	
	Rectangle rectangle;
	
	
public:
	Bird(float length, float width) : length(length) , width(width), velocity(0.0)
	{
		coordinate.x = WIDTH/2;
		coordinate.y = HEIGHT/2;
		
		rectangle = {coordinate.x, coordinate.y, length, width};
		
		jumpSound = LoadSound("jumpSound.mp3");
	}
	
	Rectangle GetRectangle() const
	{
		return rectangle;
	}
	
	// Need to finish this up:
	/*
	RectCoordinates GetRectCoordinates() const
	{
		RectCoordinates temp;
		
		temp.topLeft = coordinate;
		temp.topRight = {coordinate.x + (length * cos(0.4*atan(velocity/300.0))), coordinate.y - (length * sin(0.4*atan(velocity/300.0)))};
		temp.bottomLeft = 
		temp.bottomRight = 
		
		return temp;
	}
	*/
	
	void Update()
	{
		if(IsKeyPressed(KEY_SPACE))
		{
			velocity = -sqrt(2 * GRAVITY * (HEIGHT * 0.1));		// jump about 10 percent of the height ( u = sqrt(2gs) , where s = HEIGTH*0.1 )	
			PlaySound(jumpSound);
		}
		
		velocity += GRAVITY * GetFrameTime();
		
		coordinate.y += velocity*GetFrameTime();
		
		rectangle.x = coordinate.x;
		rectangle.y = coordinate.y;
	}
	
	void Draw()
	{
		DrawRectangle(coordinate.x, coordinate.y, length, width, YELLOW);	// Without angle
			
		// DrawRectanglePro(rectangle, {rectangle.width / 2.0f, rectangle.height / 2.0f}, 0.4*(180.0f/M_PI)*atan(velocity/300.0), YELLOW);
	}
	
	~Bird()
	{
		UnloadSound(jumpSound);
	}
};




// ============================================================================================================================



class Obstacle
{
private:
	int height;			// refers to the height of the bottom obstacle
	int width = 100;	// fixed
	
	Vector2 coordinate;
	
	bool scoreCounted;
	
public:
	Obstacle(int height) : height(height), scoreCounted(false)
	{
		coordinate.x = WIDTH;
		coordinate.y = HEIGHT - height;
	}
	
	bool isAlive()
	{
		if(coordinate.x + width > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	bool isPastBird()
	{
		if((coordinate.x < WIDTH/2) && (!scoreCounted))
		{
			scoreCounted = true;
			return true;
		}
		else
		{
			return false;
		}
	}
	
	Rectangle GetLowerRectangle() const
	{
		Rectangle temp = {coordinate.x, coordinate.y, (float)width, (float)height};
		return temp;
	}
	
	Rectangle GetUpperRectangle() const
	{
		Rectangle temp = {coordinate.x, 0, (float)width, (float)HEIGHT*0.8 - (float)height};
		return temp;
	}
	
	void Update()
	{
		// 10 seconds to cross the screen
		double secondsToCrossScreen = 10.0;
		coordinate.x -= WIDTH * GetFrameTime()/(secondsToCrossScreen);
	}
	
	void Draw()
	{
		DrawRectangle(coordinate.x, coordinate.y, width, height, GREEN);
		DrawRectangle(coordinate.x, 0, width, HEIGHT*0.8 - height, GREEN);
	}
};




// ============================================================================================================================


int main(void) 
{
	InitWindow(WIDTH, HEIGHT, "Flappy Bird");
	InitAudioDevice();
	
    SetTargetFPS(FPS);
	
	
	{
	bool GameOver = false;
	bool GameShouldStart = false;
	
	bool GameOverSoundPlayed = false;
	
	int score = 0;
	string score_string;
	
	double timeElapsed = 0.0;
	
	const int groundThickness = 10;
	Vector2 groundStartPos = {0.0,HEIGHT - groundThickness/2};
	Vector2 groundEndPos = {WIDTH, HEIGHT - groundThickness/2};
	
	
	Sound scoreSound;	
	scoreSound = LoadSound("scoreSound.mp3");
	
	Sound collisionSound;
	collisionSound = LoadSound("collisionSound.mp3");
	
	
	Bird bird(80.0,50.0);	
	vector<Obstacle> obstacles;
	
	obstacles.push_back(Obstacle((rand() % HEIGHT/2) + (HEIGHT*0.1)));

	
	while(!WindowShouldClose())
	{

		
    	BeginDrawing();
    	ClearBackground(BLACK);
    	
    	if(IsKeyPressed(KEY_SPACE))
    	{
    		GameShouldStart = true;
		}
    	
    	
   		if(!GameOver && GameShouldStart)
   		{
   			
		// ==================================================================================================================   	    	
		// UPDATE:

			timeElapsed += GetFrameTime();
			
			if(timeElapsed > 3)
			{
				obstacles.push_back(Obstacle((rand() % HEIGHT/2) + (HEIGHT*0.1)));
				timeElapsed = 0.0;
			}


	    	// OBSTACLES:	
	    	
	    	for(int i = 0; i < obstacles.size(); i++)
	    	{
	    		if(obstacles[i].isAlive())
	    		{
	    			obstacles[i].Update();
	    			if(obstacles[i].isPastBird())
	    			{
	    				score++;
	    				PlaySound(scoreSound);
					}
					if(CheckCollisionRecs(obstacles[i].GetUpperRectangle(), bird.GetRectangle()) || CheckCollisionRecs(obstacles[i].GetLowerRectangle(), bird.GetRectangle()) )
					{
						GameOver = true;	// Game should stop
					}
				}
				else
				{
					obstacles.erase(obstacles.begin() + i);
					i--;
				}
			}
	    	
	    	
	    	// BIRD:
	    	
	    	bird.Update();
	
		// ===================================================================================================================
		// DRAW:
   		
   		

		
	   		// OBSTACLES:
	   		
	    	for(int i = 0; i < obstacles.size(); i++)
	    	{
	    		obstacles[i].Draw();
			}
	    	
	    	
	    	// BIRD:
	    	
	    	bird.Draw();
	    	
	    	// GROUND:
	    	
	    	DrawLineEx(groundStartPos, groundEndPos, groundThickness, GRAY); 
	    	
	    	// SCORE:
	    	
	    	score_string = to_string(score);    	
	    	DrawText(score_string.c_str(), WIDTH/2, HEIGHT*0.2, 30, WHITE);
    	}
    	else if(!GameShouldStart)		// Game has not started yet
    	{
    		DrawText("Press Space Key To Start", WIDTH*0.2, HEIGHT*0.2, 80, WHITE);
		}
    	else		// When Game is over
    	{
    		if(!GameOverSoundPlayed)
    		{
    			PlaySound(collisionSound);
    			GameOverSoundPlayed = true;
			}
    		
    		
    		DrawText("Game Over", WIDTH*0.2, HEIGHT*0.2, 80, WHITE);
    		
    		string scoreStatement = "Final Score: " + score_string;
    		
    		DrawText(scoreStatement.c_str(), WIDTH*0.15, HEIGHT*0.4, 80, WHITE);
		}
    	
    	// ===================================================================================================================
    	EndDrawing();
	}
    
	}
	
    CloseAudioDevice();
    CloseWindow();  
    
    return 0;
}
