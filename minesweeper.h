#include <iostream>
#include <cstdlib>
#include <ctime>
#include "types.h"
#include "display_welcome.cpp"
#include <math.h> 

enum {
	MINE = 99,
	HIDDEN = 100,
};

class Minesweeper{
	
  private:
	u8 firstMove;
	u8 gameOver ;
	u8 gameWon;

	u32 clearedTiles;
	u32 row,col;
	u32 cells;
	u32 rowDim, colDim;
    u32 mines;

    u32** realBoard;
	u32** UIBoard;

	
    void makeMove()
    {
		//asks user for x and y cor of the next move		
		std::cout << "\nSelect Row: ";
		std::cin >> row;
		std::cout << "Select Column: ";
		std::cin >> col;

		row--;
		col--;

		if  ((row >= rowDim) || (col >= colDim))
		{
			std::cout << "Input is out of bounds";
			makeMove();
			return;
		}

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
      u32 mine_row;
	  u32 mine_col;
	  u32 counter = 0;
	  
      //srand(time(NULL));
      while(counter < mines)
      {
        mine_row = rand() %rowDim;
        mine_col = rand() %colDim;
        if(realBoard[mine_row][mine_col] != MINE && !(mine_row == row && mine_col == col))
        {
          realBoard[mine_row][mine_col] = MINE;
          counter++;
        }
		std::cout<<"mine: ("<<mine_row<<",";
		std::cout<<mine_col<<")"<<std::endl;
		
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
		for (u32 rowIndex = 0; rowIndex<rowDim; rowIndex++)
		{
			for (u32 colIndex = 0; colIndex<colDim; colIndex++)
			{
				tileMineCount = 0;

				if (realBoard[rowIndex][colIndex] == MINE)
				{
					continue;
				}
					
				if ((realBoard[rowIndex][colIndex+1] == MINE) && (colIndex+1<colDim) )
				{
					tileMineCount++;
				}
				
				if (colIndex!=0)
				{	
					if (realBoard[rowIndex][colIndex-1] == MINE)
					{
						tileMineCount++;
					}

					if ((realBoard[rowIndex+1][colIndex-1] == MINE) && (colIndex!=0) && (rowIndex+1<rowDim) )
					{
						tileMineCount++;
					}
				}
				
				if ((realBoard[rowIndex+1][colIndex] == MINE) && (rowIndex+1<rowDim) )
				{
					tileMineCount++;
				}
				
				if (rowIndex!=0)
				{		
					if ((realBoard[rowIndex-1][colIndex] == MINE) && (rowIndex!=0) )
					{
						tileMineCount++;
					}

					if ((realBoard[rowIndex-1][colIndex+1] == MINE) && (colIndex+1<colDim) && (rowIndex!=0) )
					{
						tileMineCount++;
					}
				}
				
				if ((realBoard[rowIndex+1][colIndex+1] == MINE) && (colIndex+1<colDim) && (rowIndex+1<rowDim) )
				{
					tileMineCount++;
				}
				

				
				if (rowIndex!=0 && colIndex!=0)
				{
					if ((realBoard[rowIndex-1][colIndex-1] == MINE) && (colIndex!=0) && (rowIndex!=0) )
					{
						tileMineCount++;
					}
				}
				realBoard[rowIndex][colIndex] = tileMineCount;
				std::cout<<"coords: ("<<rowIndex<<","<<colIndex<<")";
				std::cout<<": Surrounding Mines: "<<tileMineCount<<std::endl;
			}
		}
	}

	void initUIBoard() {
		for (u32 i = 0; i < rowDim; i++) {
			for (u32 j = 0; j < colDim; j++) {
				UIBoard[i][j] = HIDDEN;
			}
		}
	}
	
	

  public:
	/* Constructor */
    Minesweeper(u32 rowSize, u32 colSize)
    {
		firstMove = '1';
		gameOver = '0';
		gameWon = '0';
		clearedTiles = 0;
		
		cells = rowSize*colSize;

		rowDim = rowSize;
		colDim = colSize;
		realBoard = new u32*[rowSize];
		UIBoard = new u32*[rowSize];

		mines = (rowSize*colSize)/(sqrt(rowSize*colSize) - 1);

		for(u32 i = 0; i < rowSize+1; i++)
		{
    		realBoard[i] = new u32[colSize];
			UIBoard[i] = new u32[colSize];
		}
		welcome();
		initUIBoard();
		reInitDisplay();
    }
	
	
	void selectTile()
	{
		while( (gameOver == '0') )
		{
			makeMove();
			std::cout<<std::endl<<std::endl;
			system ("CLS");
			if (realBoard[row][col] != MINE)
			{
				if (UIBoard[row][col] == HIDDEN)
				{
					clearedTiles++;
				}

				UIBoard[row][col] = (u8) realBoard[row][col];
				
				welcome();
				/* To display realBoard for debugging purposes, comment reInitDisplay() and uncomment reInitDisplay() */
				reInitDisplay();
				//debug();
				if (clearedTiles == rowDim*colDim - mines)
				{
					std::cout<<"YOU WIN!"<<std::endl;
					return;
				}
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
		for(u32 rowIndex = 0; rowIndex < rowDim; rowIndex++)
		{
			for(u32 colIndex = 0; colIndex < colDim; colIndex++)
			{
				if (UIBoard[rowIndex][colIndex] == HIDDEN)
					std::cout<<"X"<<" "<<std::flush;
				else
					std::cout<<UIBoard[rowIndex][colIndex]<<" "<<std::flush;
			}
			std::cout<<std::endl;
		}
	}

	void debug()
	{
		for(u32 rowIndex = 0; rowIndex < rowDim; rowIndex++)
		{
			for(u32 colIndex = 0; colIndex < colDim; colIndex++)
			{
				std::cout<<realBoard[rowIndex][colIndex]<<" "<<std::flush;
			}
			std::cout<<std::endl;
		}
	}	

};
