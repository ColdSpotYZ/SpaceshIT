#pragma once

// Standard Library
#include <stdlib.h>
#include <string>
#include <iostream>

// SFML libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

// User-defined
#include "Menu.h"

//Game engine class

class Game
{
private:
	
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Typography
	sf::Font mainFont;

	// Main Menu
	Menu* playButton;

	void initVariables();
	void initWindow();
	void initMenu();
	void initFonts();

	// Flags
	bool gameStart;

public:
	// Constructor & Destructor
	Game();
	virtual ~Game();

	// Accessors
	const bool getWindowIsOpen() const;

	// Functions
	void pollEvents();
	void updateMousePosition();
	void update();
	void render();
};

