#include "game.h"

int main()
{
	game* newGame = new game();
	newGame->init();
	newGame->start();
	return 0;
}
