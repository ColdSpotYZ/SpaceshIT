#include "stdafx.h"
#include <iostream>
#include "Game.h"
#include <time.h>

int main()
{
	srand(time(NULL));
	// Init game object
	Game game;
	
	// Game loop (should be moved into game class)
	game.run();

	return 0;
}