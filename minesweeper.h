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
	u32 xCor,yCor;
	u32 cells;
	u32 xDim, yDim;
	
    u32** realBoard;
	u32** UIBoard;

	
    void makeMove()
    {
		//asks user for x and y cor of the next move		
		std::cout << "enter x: ";
		std::cin >> xCor;
		std::cout << "enter y: ";
		std::cin >> yCor;
			  
		switch(firstMove)
		{
			default: break;
			
			case '1': minesInit();
					numbersInit();
					firstMove = '0';
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
        mine_x = rand() %xDim;
        mine_y = rand() %yDim;
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
		u32 tileMineCount;
		for (u32 x = 0; x<xDim; x++)
		{
			for (u32 y = 0; y<yDim; y++)
			{
				tileMineCount = 0;

				if (realBoard[x][y] == MINE)
				{
					continue;
				}
					
				if ((realBoard[x][y+1] == MINE) && (y+1<yDim) )
				{
					tileMineCount++;
				}
				
				if (y!=0)
				{	
					if (realBoard[x][y-1] == MINE)
					{
						tileMineCount++;
					}
				}
				
				if ((realBoard[x+1][y] == MINE) && (x+1<xDim) )
				{
					tileMineCount++;
				}
				
				if (x!=0)
				{		
					if ((realBoard[x-1][y] == MINE) && (x!=0) )
					{
						tileMineCount++;
					}
				}
				
				if ((realBoard[x+1][y+1] == MINE) && (y+1<yDim) && (x+1<xDim) )
				{
					tileMineCount++;
				}
				
				if (y!=0)
				{
					if ((realBoard[x+1][y-1] == MINE) && (y!=0) && (x+1<xDim) )
					{
						tileMineCount++;
					}
				}
				
				if (x!=0)
				{
					if ((realBoard[x-1][y+1] == MINE) && (y+1<yDim) && (x!=0) )
					{
						tileMineCount++;
					}
				}
				
				if (x!=0 && y!=0)
				{
					if ((realBoard[x-1][y-1] == MINE) && (y!=0) && (x!=0) )
					{
						tileMineCount++;
					}
				}
				realBoard[x][y] = tileMineCount;
				std::cout<<"coords: ("<<x<<","<<y<<")";
				std::cout<<": Surrounding Mines: "<<tileMineCount<<std::endl;
			}
		}
	}
	
	

  public:
	/* Constructor */
    Minesweeper(u32 xSize, u32 ySize)
    {
		mines = '2';
		firstMove = '1';
		gameOver = '0';
		gameWon = '0';
		clearedTiles = '0';
		
		cells = 16;

		yDim = ySize;
		xDim = xSize;
		realBoard = new u32*[xSize];
		UIBoard = new u32*[xSize];
		for(u32 i = 0; i < xSize+1; i++)
		{
    		realBoard[i] = new u32[ySize];
			UIBoard[i] = new u32[ySize];
		}
    }
	
	
	void selectTile()
	{
		while( (gameOver == '0') )
		{
			makeMove();
			reInitDisplay();
			if (realBoard[xCor][yCor] != MINE)
			{
				UIBoard[xCor][yCor] = realBoard[xCor][yCor];
				std::cout<<realBoard[xCor][yCor]<<std::endl;
			}
			else 
			{
				gameOver = '1';
				std::cout<<"MINE! you loose"<<std::endl;
			}
		}
	}

	void reInitDisplay()
	{
		for(u32 x = 0; x < xDim; x++)
		{
			for(u32 y = 0; y < yDim; y++)
			{
				std::cout<<realBoard[x][y]<<" ";
			}
			std::cout<<std::endl;
		}
	}
	

};
