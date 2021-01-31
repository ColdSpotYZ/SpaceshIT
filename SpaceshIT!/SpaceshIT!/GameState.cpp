#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) 
	: State(window)
{
}

GameState::~GameState()
{
}

void GameState::endState()
{
	// End game state
}

void GameState::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void GameState::update(const float& dt)
{
	// GameState updates
	this->updateKeybinds(dt);
}

void GameState::render(sf::RenderTarget* target)
{
}
