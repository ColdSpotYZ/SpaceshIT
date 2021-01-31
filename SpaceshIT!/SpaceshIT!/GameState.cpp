#include "GameState.h"

void GameState::initPlayer()
{
}

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

void GameState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void GameState::update(const float& dt)
{
	// GameState updates
	this->updateInput(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	this->player1->render(target);
}
