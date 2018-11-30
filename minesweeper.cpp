#include "types.h"
#include "minesweeper.h"

void playGame(void);

int main(void)
{
	playGame();
	return 0;
}

void playGame(void)
{
	minesweeper game;
	game.selectTile();
}
