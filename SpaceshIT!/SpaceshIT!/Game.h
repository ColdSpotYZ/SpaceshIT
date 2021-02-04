#pragma once

// Standard Library
#include <stdlib.h>
#include <string>
#include <iostream>

// User-defined
#include "GameState.h"
#include "MainMenuState.h"
#include "Player.h"
#include "Bullet.h"


//Game engine class

class Game
{
private:
	
	// Window
	sf::RenderWindow* window;
	sf::Event ev;
	vector<sf::VideoMode> videoModes;
	bool isFullscreen;
	sf::ContextSettings windowSettings;

	// Time
	sf::Clock dtClock;
	float dt;

	// States
	Stack<State*> states;

	// Keybinds
	std::map<string, int> supportedKeys;

	// Mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Typography
	sf::Font mainFont;


	// GUI
	sf::Text playerWin;

	// World
	sf::Texture worldBackgroundTexture;
	sf::Sprite worldBackgroundSprite;

	// Initialization functions
	void initVariables();
	void initWindow();
	void initStates();
	void initKeys();
	void initFonts();
	void initWorld();
	/*void initGUI();*/

	// Flags
	bool isFocus = true;

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
	void updateDt();
	void pollEvents();

	void endApp();

	void updateInput();
	void updateMousePosition();
	void updateWorld();

	void run();

	void renderWorld();
	void update();
	void render();
};

