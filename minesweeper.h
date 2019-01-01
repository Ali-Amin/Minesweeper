#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "types.h"
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

		/* Decrement input to accomodate array index starting at 0 */
		row--;
		col--;

		/* Check if input is in bounds */
		if  ((row >= rowDim) || (col >= colDim))
		{
			std::cout << "Input is out of bounds";
			/* Repeat input prompt until valid input */
			makeMove();
			return;
		}

		/* if first move initialize game matrix */
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
      }
    }
	
	/*
	BRUTE FORCE
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
			}
		}
	}

	/* Initialize all elements of UIBoard as Hidden */
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

		/* Function in size of game matrix to calculate appropriate number of mines */
		mines = (rowSize*colSize)/(sqrt(rowSize*colSize) - 1);

		for(u32 i = 0; i < rowSize+1; i++)
		{
    		realBoard[i] = new u32[colSize];
			UIBoard[i] = new u32[colSize];
		}
		/*Clears display */
		system ("CLS");
		/*Prints Title*/
		msWelcome();
		
		initUIBoard();

		/* Re display the Game Matrix */
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
				/* Count number of cleared mines to know when the user has won */
				if (UIBoard[row][col] == HIDDEN)
				{
					clearedTiles++;
				}
				/* Get value of selected coordinate in realBoard */
				UIBoard[row][col] = realBoard[row][col];
				
				msWelcome();
				/* To display realBoard for debugging purposes, comment reInitDisplay() and uncomment reInitDisplay() */
				reInitDisplay();
				//debug();

				/* If all tiles are cleared, inform user of successfully winning */
				if (clearedTiles == rowDim*colDim - mines)
				{
					msWelcome();
					/* To display realBoard for debugging purposes, comment reInitDisplay() and uncomment reInitDisplay() */
					reInitDisplay();
					//debug();
					std::cout<<"YOU WIN!"<<std::endl;
					return;
				}
			}

			/* The user has selected on a mine tile */
			else 
			{
				msWelcome();
				UIBoard[row][col] = realBoard[row][col];
				/* To display realBoard for debugging purposes, comment reInitDisplay() and uncomment reInitDisplay() */
				reInitDisplay();
				//debug();
				gameOver = '1';
				std::cout<<"MINE! you loose"<<std::endl<<std::flush;
				
			}

		}
	}

	void reInitDisplay()
	{
		for(u32 rowIndex = 0; rowIndex < rowDim; rowIndex++)
		{
			for(u32 colIndex = 0; colIndex < colDim; colIndex++)
			{
				/* If current tile is hidden print X */
				if (UIBoard[rowIndex][colIndex] == HIDDEN)
					std::cout<<"X"<<" "<<std::flush;
				/* If current tile is a mine print M*/
				else if (UIBoard[rowIndex][colIndex] == MINE)
					std::cout<<"M"<<" "<<std::flush;
				/* If current tile is cleared print its corresponding number */
				else
					std::cout<<UIBoard[rowIndex][colIndex]<<" "<<std::flush;
			}
			std::cout<<std::endl;
		}
	}

	/* Use this instead of reInitDisplay() to display realBoard instead of UIBoard */
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

	/* Prints title message art */
	void msWelcome(void)
	{
	    std::string line;
	    std::ifstream inFile("minesweeper_art.txt");
	    if(!inFile.is_open())
	    {
	        std::cerr << "cant open file";
	        exit(0);
	    }
	    while(std::getline(inFile,line))
	    {
	        std::cout << line << std::endl;
	    }
	    inFile.close();
	}

};
