#include "stdafx.h"
#include <iostream>
#include "Game.h"

int main()
{
	// Init game object
	Game game;
	
	// Game loop (should be moved into game class)
	game.run();

	return 0;
}