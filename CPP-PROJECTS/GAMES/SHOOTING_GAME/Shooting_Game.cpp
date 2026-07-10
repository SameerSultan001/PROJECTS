#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "raylib.h"

using namespace std;


#define WIDTH 900
#define HEIGHT 600
#define FPS 120

#define GROUND_Y (HEIGHT*0.8) // at this position, GROUND_THICKNESS/2 pixels up and down
#define GROUND_THICKNESS 5

#define BULLET_SIZE 10

// Compilation: g++ Shooting_Game.cpp -o Shooting_Game $(pkg-config --cflags --libs raylib)


class Gun // player class (A 50 by 50 square)
{
	private:
		
		// ====== DATA =========================
	
		int length;
		Vector2 position;
		int speed;
		Color color;
		
		// ====== HELPER FUNCTIONS =============	
		
		void MoveLeft()
		{
			position.x -= speed;
			
			if(position.x < 0)
			{
				position.x = 0;
			}
		}
		
		void MoveRight()
		{
			position.x += speed;
			
			if(position.x > (WIDTH - length))
			{
				position.x = WIDTH - length;
			}	
		}		
		
	public:
		// ====== CONSTRUCTOR ====================
		
		Gun() : length(50), speed(2), color(WHITE) 
		{
			position.x = (WIDTH/2) - (length/2);
			position.y = GROUND_Y - length - (GROUND_THICKNESS/2);
		}
		

		
		// ====== MEMBER FUNCTIONS =================
		
		void SetSpeed(int speed)
		{
			this->speed = speed;
		}
		
		
		void Update()
		{
			if(IsKeyDown(KEY_LEFT))
            {
                MoveLeft();
            }

            if(IsKeyDown(KEY_RIGHT))
            {
                MoveRight();              
            }
		}
		
		
		
		void Draw() const
		{
			DrawRectangle(position.x, position.y, length, length, color);
		}
		
		
		Vector2 GetMuzzlePosition() const	// the top left corner of the muzzle (consider the muzzle to be a square)
        {
            Vector2 muzzlePosition;
            muzzlePosition.x = position.x + length/2 - BULLET_SIZE/2;
            muzzlePosition.y = position.y - BULLET_SIZE;
            return muzzlePosition;
        }
        
        
}; // END Gun CLASS




class Bullet // each bullet would be represented by a Bullet object (A 10 by 10 Square)
{
	private:
		// ====== DATA =========================
		
		int length; 
		int speed;
		Vector2 position;
		bool isAlive;
		Color color;
		
		
	public:
		// ====== CONSTRUCTOR ====================
		
		Bullet(Vector2 gunMuzzlePosition) : length(BULLET_SIZE) , speed(2) , position(gunMuzzlePosition) , isAlive(true), color(RED) {}
		
		
		
		// ====== MEMBER FUNCTIONS =================
		
		void SetSpeed(int speed)
		{
			this->speed = speed;
		}		
		
		
		bool GetAliveStatus() const
		{
			return isAlive;
		}
		
		
		void SetAliveStatus()
		{
			isAlive = false;
		}
		
		
		Rectangle GetRectangle() const
		{
			Rectangle rectangle;
			
			rectangle.x = position.x;
			rectangle.y = position.y;
			rectangle.width = length;
			rectangle.height = length;
			
			
			return rectangle;
		}
		
		
		void Update()
		{
			position.y -= speed;	// bullet goes up
			
			if(position.y < 0)
			{
				isAlive = false;
			}
		}
		

		void Draw() const
		{
			DrawRectangle(position.x, position.y, length, length, color);
		}
		
		
		
}; // END Bullet CLASS







class Target // A 30 by 30 square
{
	private:
		// ====== DATA =========================
	
		int length;		// 30 by 30
		double speed;		// GROUND_Y / 8 	(8 seconds to reach the ground)
		Vector2 position;
		bool alive;	// To check for impact with a bullet
		bool atGround; 	// To check for impact with the ground to make the game stop (game over)
		Color color;
	
	
	public:
		// ====== CONSTRUCTOR ====================
	
		Target(int TargetXPosition) : length(30), speed(GROUND_Y / (8 * FPS)), alive(true), atGround(false), color(GREEN)
		{
			position.x = TargetXPosition;
			position.y = -length;
		}
		
		
		
		// ====== MEMBER FUNCTIONS =================	
		
		void Update()
		{
			position.y += speed;	// target goes down
			
			if((position.y + length) >= GROUND_Y)
			{
				atGround = true;
			}
			
		}
		
		
		bool isAtGround() const
		{
			return atGround;
		}
	
	
		bool isAlive() const
		{
			return alive;
		}
		
		
		void SetAliveStatus()
		{
			alive = false;
		}
		
		
		Rectangle GetRectangle() const
		{
			Rectangle rectangle;
			
			rectangle.x = position.x;
			rectangle.y = position.y;
			rectangle.width = length;
			rectangle.height = length;
			
			
			return rectangle;
		}
		
		
		void Draw() const
		{
			DrawRectangle(position.x, position.y, length, length, color);
		}
	
}; // END Target CLASS






class Game
{
	private:
		// ====== DATA =========================
		
		int height;
		int width;
		float ground_y;
		float groundThickness;
		Vector2 groundStartPos;
		Vector2 groundEndPos;
		double timeElapsed;
		int level;
		int numTargets = 0;
		float spawnTime;
		bool GameOver;
		
		
		Gun player;
		
		vector<Bullet> bullets;
		vector<Target> allTargets;
		vector<Target> targets;
		
		
		// ====== HELPER FUNCTIONS =============	
		
		string BuildFileName(int level)
		{
			string fileName;
			fileName = "Level" + to_string(level) + ".txt";
			
			return fileName;
		}
		
		
		
		bool SetTargets()
		{
			int num; 	// used as a temporary variable
			string FileName = BuildFileName(level);
			
			ifstream File(FileName.c_str());
			
			if(!File)	// check if file was opened successfully
			{
				cout << "Could not open file: " << FileName << endl;	// for debugging
				return false;
			}
			
			File >> spawnTime;
			
			while(File >> num)
	        {
	            allTargets.push_back(Target(num));
	        }
	
	        File.close();
			
			return true;
		}
		
		
	public:
		// ====== CONSTRUCTOR ====================
		
		Game(int level) : level(level) , height(HEIGHT) , width(WIDTH) , ground_y(GROUND_Y) , timeElapsed(0.0) , GameOver(false)
		{
			SetTargets();	//	Set up our array of targets first from the input file based on the file level.
			groundStartPos = {0, ground_y};
			groundEndPos = {WIDTH, ground_y};
			groundThickness = GROUND_THICKNESS;
		}
		
		
		
		// ====== MEMBER FUNCTIONS =================
		
		void Update()	// Updated every frame
		{
			if(!GameOver)
			{		
				timeElapsed += GetFrameTime();
				
				player.Update();
				
				
				if(IsKeyPressed(KEY_SPACE))
		        {
		            bullets.push_back(Bullet(player.GetMuzzlePosition()));
		        }
		        
		        
		        
		        for(int i = 0; i < bullets.size(); i++)
		        {
		        	bullets[i].Update();
		        	
		        	for(int j = 0; j < targets.size(); j++)
		        	{
		        		if(CheckCollisionRecs(bullets[i].GetRectangle(), targets[j].GetRectangle()))
		        		{
		        			bullets[i].SetAliveStatus();
		        			targets[j].SetAliveStatus();
		        			break;
						}
					}
		        	
		        	if(!bullets[i].GetAliveStatus())
		        	{
		        		bullets.erase(bullets.begin() + i);
		        		i--;
					}
				}
		        
		        if(timeElapsed > spawnTime)
		        {
		        	timeElapsed = 0.0;
		        	
		        	if(numTargets < allTargets.size())
		        	{	        		
		        		targets.push_back(allTargets[numTargets]);
		        		numTargets++;
		        	}
				}
		        
		        for(int i = 0; i < targets.size(); i++)
		        {
		        	targets[i].Update();
		        	
		        	if(targets[i].isAtGround())
					{
						GameOver = true;
					}
		        	if(!targets[i].isAlive())
		        	{
		        		targets.erase(targets.begin() + i);
		        		i--;
					}	
				}
			}
		}
		
		
		void Draw() const
		{
			if(!GameOver)
			{					
				// =============== DRAW PLAYER ======================
				
				player.Draw();
				
				
				// =============== DRAW BULLETS ======================
				
				for(int i = 0; i < bullets.size(); i++)
				{
					bullets[i].Draw();
				}
				
				
				// =============== DRAW TARGETS ======================
				
				for(int i = 0; i < targets.size(); i++)
				{
					targets[i].Draw();
				}
			
				
				// =============== DRAW GROUND ======================
				
				DrawLineEx(groundStartPos, groundEndPos, groundThickness, GRAY);
				
			}
			else
			{
				DrawText("Game Over!", 0.1*WIDTH, 0.2*HEIGHT, 80, RED);
			}
		}
		
		
		
}; // END Game CLASS




int main()
{
	Game game(1);
	
	InitWindow(WIDTH, HEIGHT, "Shooting Game");
    SetTargetFPS(FPS);
    
	while(!WindowShouldClose())
	{
		BeginDrawing();
		
		ClearBackground(BLACK);
		
		game.Update();
	
		game.Draw();
		
		EndDrawing();
	}
	
	
	return 0;
}
