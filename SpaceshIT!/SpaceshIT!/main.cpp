#include <iostream>
#include "Game.h"

int main()
{
	// Init game object
	Game game;
	
	// Game loop
	while (game.getWindowIsOpen())
	{
		//Update
		game.update();
		//Render
		game.render();

	}

	return 0;
}