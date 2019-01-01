#include "types.h"
#include "minesweeper.h"
#include "display_welcome.cpp"
#include <stdlib.h>
#include <iostream>
#include <string>

void playGame(void);

int main(void)
{
    welcome();
	playGame();
	return 0;
}

void playGame(void)
{
    u32 rowSize, colSize;
    std::cout<<"Please enter the number of tile rows: ";
    std::cin>>rowSize;
    std::cout<<"Please enter the number of tile columns: ";
    std::cin>>colSize;

	Minesweeper game = Minesweeper(rowSize,colSize);
	game.selectTile();
}
