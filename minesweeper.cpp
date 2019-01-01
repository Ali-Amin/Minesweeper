#include "types.h"
#include "minesweeper.h"
#include <stdlib.h>
#include <iostream>
#include <string>

void playGame(void);
void startupWelcome(void);

int main(void)
{
    startupWelcome();
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


void startupWelcome(void)
{
    std::string line;
    std::ifstream inFile("welcome_start.txt");
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
