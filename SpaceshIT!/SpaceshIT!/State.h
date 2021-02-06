#pragma once
#include "Map.h"

class State
{
protected:
	Stack<State*>* states;
	sf::RenderWindow* window;
	Map<string, int>* supportedKeys;
	Map<string, int> keybinds;

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
	State(sf::RenderWindow* window, Map<string, int>* supportedKeys, Stack<State*>* states);
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

