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
	Minesweeper game = Minesweeper(4,4);
	game.selectTile();
}
