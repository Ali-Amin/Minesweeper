#include "types.h"
#include "minesweeper.h"
#include <fstream>
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
	Minesweeper game = Minesweeper(4,4);
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
