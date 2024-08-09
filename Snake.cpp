#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <windows.h>
#include <ctime>

class Fruit
{
	private:
		int xPosFruit = 10;
		int yPosFruit = 10;
	public:
		//Get and Set
		int *GetXFruit(){ return &xPosFruit;}
		int *GetYFruit(){ return &yPosFruit;}
		void ChangeFruitLocation()
		{
			xPosFruit = (rand() % 38) + 1;
			yPosFruit = (rand() % 18) + 1;
		}
		 	
};

class Snake : public Fruit
{
	private:
		//Basic Player
		int xPos;
		int yPos;
		int length = 0;
		int score = 0;
		bool isAlive = true;
		
		//Player Tails
		int tailX[40];
		int tailY[20];
	
	public:
		enum Direction
		{
			STOP,
			UP,
			DOWN,
			RIGHT,
			LEFT,
		};
		Direction dir;
		
		void HideCursor()
		{
		    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		    CONSOLE_CURSOR_INFO curInfo;
		
		    GetConsoleCursorInfo(hStdOut, &curInfo);
		    curInfo.bVisible = FALSE;
		    SetConsoleCursorInfo(hStdOut, &curInfo);
		}
		
		//Tails
		void AddTails(){ length++; }
		int *GetLength(){ return &length; }
		int *GetTailXPos(){ return tailX; }
		int *GetTailYPos(){ return tailY; }
		
		//Get Pos
		int *GetX(){ return &xPos; }
		int *GetY(){ return &yPos; }
		int *GetScore(){ return &score; }
		bool *GetAlive(){ return &isAlive; }
		
};

void Setup(Snake &player);
void UserInput(Snake &player);
void Start(Snake &player);
void Draw(Snake &player);
void ClearScreen();
void SnakeMovement(Snake &player);
void AddScore(Snake &player, int score);


int main(void)
{
	Snake player;
	
	Start(player);
	
	while(true)
	{	
		UserInput(player);
		SnakeMovement(player);
		Setup(player);
		Draw(player);
		ClearScreen();
				
	}
		

}

void Setup(Snake &player)
{
	//Game Over Screen
	if(*player.GetAlive() == false)
	{
		player.dir = player.STOP;
		system("cls");
		printf(" .d8888b.  8888888 88888888888       .d8888b.  888     888 8888888b.\n");
		printf("d88P  Y88b   888       888          d88P  Y88b 888     888 888  \"Y88b\n");
		printf("888    888   888       888          888    888 888     888 888    888 \n");
		printf("888          888       888          888        888     888 888    888\n");
		printf("888  88888   888       888          888  88888 888     888 888    888\n");
		printf("888    888   888       888          888    888 888     888 888    888\n");
		printf("Y88b  d88P   888       888          Y88b  d88P Y88b. .d88P 888  .d88P\n");
		printf(" \"Y8888P88 8888888     888           \"Y8888P88  \"Y88888P\"  8888888P\"\n");
		printf("----------------------------------------------------------------------------\n");
		printf("Score: %d\nLength: %d\n", *player.GetScore(), *player.GetLength() + 1);	
		printf("----------------------------------------------------------------------------\n");
		printf("Press R to Restart...\n");
		printf("Press ENTER 3 TIMES to End the game...");

		if(_getch() == 'r')
		{
			system("cls");
			Start(player);
			return;			
		}
		
		if(_getch() == 13)
		{
			exit(0);
		}		
		
		
	}
}

void UserInput(Snake &player)
{
	if(_kbhit())
	{
		switch(_getch())
		{
			//WASD Control
			case 'w':
				if(player.dir != player.DOWN)
				{
					player.dir = player.UP;					
				}
				break;
			case 'a':
				if(player.dir != player.RIGHT)
				{
					player.dir = player.LEFT;
				}
				break;
			case 's':
				if(player.dir != player.UP)
				{
					player.dir = player.DOWN;				
				}
				break;
			case 'd':
				if(player.dir != player.LEFT)
				{
					player.dir = player.RIGHT;
				}
				break;
		}		
	}

}

void Start(Snake &player)
{	
	player.HideCursor();
	*player.GetAlive() = true;
	*player.GetScore() = 0;
	*player.GetLength() = 0;
	player.dir = player.STOP;
	*player.GetX() = 20;
	*player.GetY() = 10;
	srand(time(NULL));
}

void SnakeMovement(Snake &player)
{		

	//tail logic
	int prevX = *player.GetX();
	int prevY = *player.GetY();
	
	switch(player.dir)
	{
		case player.STOP:
			break;
		case player.DOWN:
			*player.GetY() += 1;				
			break;
		case player.UP:
			*player.GetY() -= 1;	
			break;
		case player.RIGHT:
			*player.GetX() += 1;	
			break;					
		case player.LEFT:
			*player.GetX() -= 1;	
		 	break;
	}

	//move the tail to the prev
	for(int i = *player.GetLength(); i > 0; i--)
	{
        player.GetTailXPos()[i] = player.GetTailXPos()[i - 1];
        player.GetTailYPos()[i] = player.GetTailYPos()[i - 1];		
	}
	
	//the tail follow the player
    if (*player.GetLength() > 0) {
        player.GetTailXPos()[0] = prevX;
        player.GetTailYPos()[0] = prevY;
    }		


}
	
void ClearScreen()
{
	Sleep(100);
	system("cls");
}

void Draw(Snake &player)
{                              
	int row = 40;
	int col = 20;
	char map[col][row];
	                   
	
	for(int i = 0; i < col; i++)
	{
		for(int j = 0; j < row; j++)
		{
			//Arena Map
			if(i == 0 || j == 0 || i == col - 1 || j == row - 1)
			{
				map[i][j] = '#';
			}else{

				map[i][j] = ' ';				
			}

			//Fruit
		    int fruitX = *player.GetXFruit();
		    int fruitY = *player.GetYFruit();
			if(fruitX > 0 && fruitX < row - 1 && fruitY > 0 && fruitY < col - 1)
			{
				map[fruitY][fruitX] = 'F';
			}			
								                    
			//Player Detects Collision And Draw Player
			int playerX = *player.GetX();
			int playerY = *player.GetY();
			
			//Draw Player Tail
			int tailLength = *player.GetLength();			
			for(int i = 0; i < tailLength; i++)
			{
				map[player.GetTailYPos()[i]][player.GetTailXPos()[i]] = 'o';
			}
						
			//Player Movement and Check Walls and Tails
			if(playerX > 0 && playerX < row - 1 && playerY > 0 && playerY < row - 1 && map[playerY][playerX] != 'o' && map[playerY][playerX] != '#')
			{
				map[playerY][playerX] = 'O';
			}else
			{
				*player.GetAlive() = false;
			}
			
			//Player Detects Fruit
			if(playerX == fruitX && playerY == fruitY)
			{
				player.AddTails();
		        player.ChangeFruitLocation();
		        AddScore(player, 20);
			}				


		}
	}
	
	//Print Map
	for(int i = 0; i < col; i++)
	{
		for(int j = 0; j < row; j++)
		{
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
	
	//Make Score
	printf("Score: %d\n", *player.GetScore());	
	
	//Input Tutorial
	printf("------------------------------------------\n");
	printf("Press W to UP\n");
	printf("Press A to LEFT\n");
	printf("Press S to DOWN\n");
	printf("Press D to RIGHT\n");
	
	//For Debugging
	//printf("Fruit X: %d, Y: %d", *player.GetXFruit(), *player.GetYFruit());
}

void AddScore(Snake &player, int score)
{
	*player.GetScore() += score;
}
