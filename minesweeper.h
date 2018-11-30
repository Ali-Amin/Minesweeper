#include <iostream>
#include <cstdlib>
#include <ctime>
#include "types.h"

enum {
	MINE = 99,
};

class Minesweeper{
	
  private:
    u8 mines;
	u8 firstMove;
	u8 gameOver ;
	u8 gameWon;
	u8 clearedTiles;
	
	u32 cells;
	u32 xCor,yCor;

    u32 realBoard[4][4];
	u32 UIBoard[4][4];

	
    void makeMove()
    {
		//asks user for x and y cor of the next move		
		std::cout << "enter x: ";
		std::cin >> xCor;
		std::cout << "enter y: ";
		std::cin >> yCor;
			  
		switch(firstMove)
		{
			case 0:break;
			
			case 1: minesInit();
					numbersInit();
					firstMove = 0;
					break;
							
		}
    }	
	
	void minesInit()
    {
      //Mine locations random generation
      //player should make a first move before calling this method
      u32 mine_x;
	  u32 mine_y;
	  u8 counter = '0';
	  
      //srand(time(NULL));
      while(counter < mines)
      {
        mine_x = rand() %4;
        mine_y = rand() %4;
        if(realBoard[mine_x][mine_y] != MINE && !(mine_x == xCor && mine_y == yCor))
        {
          realBoard[mine_x][mine_y] = MINE;
          counter++;
        }
		std::cout<<"mine: ("<<mine_x<<",";
		std::cout<<mine_y<<")"<<std::endl;
		
      }
    }
	
	/*
	[x][y+1] (RIGHT)
	[x][y-1] (LEFT)
	[x+1][y] (TOP)
	[x-1][y] (BOT)
	[x+1][y+1] (BOT RIGHT)
	[x+1][y-1] (BOT LEFT)
	[x-1][y+1] (TOP RIGHT)
	[x-1][y-1] (TOP LEFT)
	*/
    void numbersInit()
    {

		for (u32 x = 0; x<4; x++)
		{
			for (u32 y = 0; y<4; y++)
			{
				u32 tileMineCount = 0;

				if (realBoard[x][y] == MINE)
				{
					std::cout<<"point 1"<<std::endl;
					continue;
				}
					
				if ((realBoard[x][y+1] == MINE) && (y+1<4) )
				{
					tileMineCount++;
					std::cout<<"point 2"<<std::endl;
				}
				
				if (y!=0)
				{	
					if (realBoard[x][y-1] == MINE)
					{
						tileMineCount++;
						std::cout<<"point 3"<<std::endl;
					}
				}
				
				if ((realBoard[x+1][y] == MINE) && (x+1<4) )
				{
					tileMineCount++;
					std::cout<<"point 4"<<std::endl;				
				}
				
				if (x!=0)
				{		
					if ((realBoard[x-1][y] == MINE) && (x!=0) )
					{
						tileMineCount++;
						std::cout<<"point 5"<<std::endl;				
					}
				}
				
				if ((realBoard[x+1][y+1] == MINE) && (y+1<4) && (x+1<4) )
				{
					tileMineCount++;
					std::cout<<"point 6"<<std::endl;					
				}
				
				if (y!=0)
				{
					if ((realBoard[x+1][y-1] == MINE) && (y!=0) && (x+1<4) )
					{
						tileMineCount++;
						std::cout<<"point 7"<<std::endl;					
					}
				}
				
				if (x!=0)
				{
					if ((realBoard[x-1][y+1] == MINE) && (y+1<4) && (x!=0) )
					{
						tileMineCount++;
						std::cout<<"point 8"<<std::endl;					
					}
				}
				
				if (x!=0 && y!=0)
				{
					if ((realBoard[x-1][y-1] == MINE) && (y!=0) && (x!=0) )
					{
						tileMineCount++;
						std::cout<<"point 9"<<std::endl;					
					}
				}
				
				std::cout<<"point 10"<<std::endl;
				std::cout<<"coords: ("<<x<<",";
				std::cout<<y<<")";
				std::cout<<": mineNumber: "<<tileMineCount<<std::endl;
			}
		}
	}
	
	

  public:
	/* Constructor */
    minesweeper()
    {
		mines = '2';
		firstMove = '1';
		gameOver = '0';
		gameWon = '0';
		clearedTiles = '0';
		
		cells = 16;
		
    }
	

	void selectTile()
	{
		while( (gameOver == '0') )
		{
			makeMove();
			if (realBoard[xCor][yCor] != MINE)
			{
				UIBoard[xCor][yCor] = realBoard[xCor][yCor];
				std::cout<<realBoard[xCor][yCor]<<std::endl;
			}
			else 
			{
				gameOver = 1;
				std::cout<<"MINE: "<<realBoard[xCor][yCor]<<std::endl;
			}
		}
	}
	

};
