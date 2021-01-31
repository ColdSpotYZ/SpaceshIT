#pragma once

// Standard Library
#include <stdlib.h>
#include <string>
#include <iostream>

// User-defined
#include "Menu.h"
#include "GameState.h"
#include "Player.h"


//Game engine class

class Game
{
private:
	
	// Window
	sf::RenderWindow* window;
	sf::Event ev;

	// Time
	sf::Clock dtClock;
	float dt;

	// States
	//Stack<State*> states;

	// Mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Typography
	sf::Font mainFont;

	// Main Menu
	Menu* playButton;

	// GUI
	sf::Text playerWin;
	sf::RectangleShape player1HpBar;
	sf::RectangleShape player1HpBarBack;
	sf::RectangleShape player2HpBar;
	sf::RectangleShape player2HpBarBack;



	// World
	sf::Texture worldBackgroundTexture;
	sf::Sprite worldBackgroundSprite;

	// Initialization functions
	void initVariables();
	void initWindow();
	void initStates();
	void initMenu();
	void initFonts();
	void initWorld();
	void initGUI();

	// Player
	Vector<Player*>* playerVec;
	Player* player1;
	Player* player2;
	void initPlayer();

	// Flags
	bool gameStart;
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
	void updateGUI();
	void updateWorld();
	void updateCollision();

	void renderWorld();
	void update();
	void render();
};

