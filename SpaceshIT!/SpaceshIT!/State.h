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
	Vector<sf::Texture> textures;
	bool quit;

	// Mouse position
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

public:
	State(sf::RenderWindow* window, Stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	virtual void updateMousePosition();
	virtual void updateInput(const float& dt) = 0;
	virtual void checkForQuit();
	virtual void endState() = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target=nullptr) = 0;
};

