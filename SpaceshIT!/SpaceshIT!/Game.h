#pragma once

// Standard Library
#include <stdlib.h>
#include <string>
#include <iostream>

// User-defined
#include "Menu.h"
#include "Player.h"
#include "Vector.h"


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

	// GUI

	// World
	sf::Texture worldBackgroundTexture;
	sf::Sprite worldBackgroundSprite;

	// Initialization functions
	void initVariables();
	void initWindow();
	void initMenu();
	void initFonts();
	void initWorld();

	// Player
	Vector<Player>* playerVec;
	std::vector<Player>* temp;
	Player* player1;
	Player* player2;
	void initPlayer();

	// Flags
	bool gameStart;

public:
	// Constructor & Destructor
	Game();
	virtual ~Game();

	/* Accessors */

	////////////////////////////////////////////////////////////
	/// \brief Check if window object is open
	///
	/// While the window object exists,
	/// the function will return a non-zero value
	///
	///
	/// \return true if windows object exist, false if does not exist
	///
	////////////////////////////////////////////////////////////
	const bool getWindowIsOpen() const;

	// Functions
	void pollEvents();

	void updateInput();
	void updateMousePosition();
	void updateGUI();
	void updateWorld();
	void updateCollision();

	void renderWorld();
	void update();
	void render();
};

