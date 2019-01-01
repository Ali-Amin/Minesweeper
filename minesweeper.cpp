#include "types.h"
#include "minesweeper.h"
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <string>

void playGame(void);
void welcome(void);

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

void welcome(void)
{
    std::string line;
    std::ifstream inFile("welcome_art.txt");
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
