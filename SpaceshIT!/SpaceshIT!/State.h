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
private:
	sf::RenderWindow* window;
	Vector<sf::Texture> textures;
	bool quit;

public:
	State(sf::RenderWindow* window);
	virtual ~State();

	const bool& getQuit() const;
	virtual void updateInput(const float& dt) = 0;
	virtual void checkForQuit();
	virtual void endState() = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target=nullptr) = 0;
};

