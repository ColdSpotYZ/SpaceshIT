#include <iostream>
#include "Game.h"

int main()
{
	// Init game object
	Game game;

	// Initialize music (should be moved into game class)
	sf::Music music;
	if (!music.openFromFile("Assets/Audio/theme.wav"))
		std::cout << "Unable to load music" << std::endl;
	else
	{
		music.setLoop(true);
		music.setVolume(25);
		music.play();
	}
		
	
	// Game loop (should be moved into game class)
	while (game.getWindowIsOpen())
	{
		//Update
		game.update();
		//Render
		game.render();

	}

	return 0;
}