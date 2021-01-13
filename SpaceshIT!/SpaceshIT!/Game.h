#pragma once

#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//Game engine class

class Game
{
private:
	
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	void initVariables();
	void initWindow();

public:
	// Constructor & Destructor
	Game();
	virtual ~Game();

	// Accessors
	const bool getWindowIsOpen() const;

	// Functions
	void pollEvents();
	void update();
	void render();
};

