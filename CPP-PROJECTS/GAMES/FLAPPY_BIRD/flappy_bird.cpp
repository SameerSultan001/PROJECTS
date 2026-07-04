#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>	// for rand() 
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
    Vector2 bottomRight;
    Vector2 bottomLeft;
};

// This function was written by ChatGPT:
float Dot(Vector2 a, Vector2 b)
{
    return a.x*b.x + a.y*b.y;
}

// This function was written by ChatGPT:
Vector2 Normalize(Vector2 v)
{
    float len = sqrt(v.x*v.x + v.y*v.y);

    if(len==0)
        return {0,0};

    return {v.x/len, v.y/len};
}

// This function was written by ChatGPT
void Project(Vector2 axis, Vector2 points[4], float &min, float &max)
{
    min = Dot(points[0],axis);
    max = min;

    for(int i=1;i<4;i++)
    {
        float p = Dot(points[i],axis);

        if(p<min) min=p;
        if(p>max) max=p;
    }
}

// This function was written by ChatGPT:
bool CheckCollisionRecsZ(RectCoordinates A, RectCoordinates B)
{
    Vector2 a[4] =
    {
        A.topLeft,
        A.topRight,
        A.bottomRight,
        A.bottomLeft
    };

    Vector2 b[4] =
    {
        B.topLeft,
        B.topRight,
        B.bottomRight,
        B.bottomLeft
    };

    Vector2 axes[4];

    axes[0] = Normalize({ -(a[1].y - a[0].y), a[1].x - a[0].x });

    axes[1] = Normalize({ -(a[2].y - a[1].y), a[2].x - a[1].x });

    axes[2] = Normalize({ -(b[1].y - b[0].y), b[1].x - b[0].x });

    axes[3] = Normalize({ -(b[2].y - b[1].y), b[2].x - b[1].x });

    for(int i=0;i<4;i++)
    {
        float minA,maxA;
        float minB,maxB;

        Project(axes[i],a,minA,maxA);
        Project(axes[i],b,minB,maxB);

        if(maxA < minB || maxB < minA)
            return false;
    }

    return true;
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
	
	// This function was written by ChatGPT:
	RectCoordinates GetRectCoordinates() const
	{
	    RectCoordinates rect;
	
	    float angle = 0.4f * atan(velocity / 300.0);
	
	    float c = cos(angle);
	    float s = sin(angle);
	
	    Vector2 center =
	    {
	        rectangle.x,
	        rectangle.y
	    };
	   
	
	    Vector2 local[4] =
	    {
	        {-length/2.0f, -width/2.0f},
	        { length/2.0f, -width/2.0f},
	        { length/2.0f,  width/2.0f},
	        {-length/2.0f,  width/2.0f}
	    };
	
	    Vector2 world[4];
	
	    for(int i=0;i<4;i++)
	    {
	        world[i].x = center.x + local[i].x*c - local[i].y*s;
	        world[i].y = center.y + local[i].x*s + local[i].y*c;
	    }
	
	    rect.topLeft     = world[0];
	    rect.topRight    = world[1];
	    rect.bottomRight = world[2];
	    rect.bottomLeft  = world[3];
	
	    return rect;
	}
	
	
	void Reset()
	{
		coordinate.x = WIDTH/2;
		coordinate.y = HEIGHT/2;
		
		rectangle = {coordinate.x, coordinate.y, length, width};
		
		velocity = 0.0;		
	}
	
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
		//DrawRectangle(coordinate.x, coordinate.y, length, width, YELLOW);	// Without angle
			
		DrawRectanglePro(rectangle, {rectangle.width / 2.0f, rectangle.height / 2.0f}, 0.4*(180.0f/M_PI)*atan(velocity/300.0), YELLOW);
		
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
	
	/*
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
	*/
	
	// This function was written by ChatGPT:
	RectCoordinates GetLowerRectCoordinates() const
	{
	    RectCoordinates r;
	
	    r.topLeft     = {coordinate.x, coordinate.y};
	    r.topRight    = {coordinate.x + width, coordinate.y};
	    r.bottomRight = {coordinate.x + width, coordinate.y + height};
	    r.bottomLeft  = {coordinate.x, coordinate.y + height};
	
	    return r;
	}
	
	// This function was written by ChatGPT:
	RectCoordinates GetUpperRectCoordinates() const
	{
	    float h = HEIGHT * 0.8f - height;
	
	    RectCoordinates r;
	
	    r.topLeft     = {coordinate.x, 0};
	    r.topRight    = {coordinate.x + width, 0};
	    r.bottomRight = {coordinate.x + width, h};
	    r.bottomLeft  = {coordinate.x, h};
	
	    return r;
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
	int highScore = 0;
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
	
	obstacles.push_back(Obstacle((rand() % (HEIGHT/2)) + (HEIGHT*0.1)));

	
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
				obstacles.push_back(Obstacle((rand() % (HEIGHT/2)) + (HEIGHT*0.1)));
				timeElapsed = 0.0;
			}
			
			
			// BIRD:
	    	
	    	bird.Update();

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
					if(CheckCollisionRecsZ(obstacles[i].GetUpperRectCoordinates(), bird.GetRectCoordinates()) || CheckCollisionRecsZ(obstacles[i].GetLowerRectCoordinates(), bird.GetRectCoordinates()) || bird.GetRectCoordinates().bottomRight.y >= HEIGHT || bird.GetRectCoordinates().topRight.y <= 0.0)
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
    		
    		
    		DrawText("Game Over", WIDTH*0.2, HEIGHT*0.2, 80, RED);
    		
    		string scoreStatement = "Final Score: " + score_string;
    		
    		DrawText(scoreStatement.c_str(), WIDTH*0.15, HEIGHT*0.4, 80, WHITE);
    		
    		
    		
    		if(score > highScore)
    		{
    			highScore = score;
			}
			
			string highScoreStatement = "High Score: " + to_string(highScore);
    		DrawText(highScoreStatement.c_str(), WIDTH*0.15, HEIGHT*0.6, 80, WHITE);
    		
    		DrawText("Press Space To Retry", WIDTH*0.15, HEIGHT*0.8, 80, WHITE);
    		
    		if(IsKeyPressed(KEY_SPACE))
    		{
    			GameOver = false;
    			GameShouldStart = true;
    			GameOverSoundPlayed = false;
    			
    			timeElapsed = 0;
    			score = 0;
    			
    			bird.Reset();
    			obstacles.clear();
    			
    			obstacles.push_back(Obstacle((rand() % (HEIGHT/2)) + (HEIGHT*0.1)));
			}
		}
    	
    	// ===================================================================================================================
    	EndDrawing();
	}
    
	}
	
    CloseAudioDevice();
    CloseWindow();  
    
    return 0;
}
