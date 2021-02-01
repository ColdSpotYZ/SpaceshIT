#include <iostream>
#include "Game.h"

int main()
{
	// Init game object
	Game game;
	
	// Game loop (should be moved into game class)
	while (game.getWindowIsOpen())
	{
		//Update Delta Time
		game.updateDt();
		//Update
		game.update();
		//Render
		game.render();

	}

	return 0;
}