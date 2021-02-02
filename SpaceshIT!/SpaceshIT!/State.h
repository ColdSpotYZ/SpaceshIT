#pragma once

#include <fstream>
#include <sstream>

#include "Vector.h"
#include "Stack.h"
//#include "Map.h"

// SFML include
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class State
{
protected:
	Stack<State*>* states;
	sf::RenderWindow* window;
	std::map<string, int>* supportedKeys;
	std::map<string, int> keybinds;

	Vector<sf::Texture> textures;
	bool quit;
	bool paused;
	float keyTime;
	float keyTimeMax;

	// Mouse position
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Initializers
	virtual void initKeybinds() = 0;

public:
	State(sf::RenderWindow* window, std::map<string, int>* supportedKeys, Stack<State*>* states);
	virtual ~State();

	// Accessors
	const bool& getQuit() const;
	const bool getKeyTime();


	// Functions
	virtual void updateMousePosition();
	virtual void updateKeyTime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void endState() = 0;
	void pauseState();
	void unpauseState();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target=nullptr) = 0;
};

