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
#include "Map.h"

//Game engine class

class Game
{
private:
	class GraphicsSettings
	{
	public:
		GraphicsSettings()
		{
			this->resolution = sf::VideoMode::getDesktopMode();
			this->fullscreen = false;
			this->verticalSync = false;
			this->frameRateLimit = 144;
			this->contextSettings.antialiasingLevel = 0;
			for (unsigned i = 0; i < sf::VideoMode::getFullscreenModes().size(); i++)
				this->videoModes.push_back(sf::VideoMode::getFullscreenModes()[i]);
		}
		// Variables
		sf::VideoMode resolution;
		bool fullscreen;
		bool verticalSync;
		unsigned frameRateLimit;
		sf::ContextSettings contextSettings;
		Vector<const sf::VideoMode> videoModes;

		// Functions
		void saveToFile(const std::string path);

		void loadFromFile(const std::string path);
	};
	
	// Window
	sf::RenderWindow* window;
	sf::Event ev;
	vector<sf::VideoMode> videoModes;
	bool isFullscreen;
	sf::ContextSettings windowSettings;

	// Resources 
	

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

