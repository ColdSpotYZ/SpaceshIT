#include "GameState.h"

void GameState::initVariables()
{
	this->playerVec = new Vector<Player*>;
}

void GameState::initPlayer()
{
	this->player1 = new Player((char*)"player1");
	this->player2 = new Player((char*)"player2");
	this->playerVec->push_back(this->player1);
	this->playerVec->push_back(this->player2);
}

GameState::GameState(sf::RenderWindow* window)
	: State(window)
{
	initVariables();
	initPlayer();
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
	std::cout << "Gamestate check for input" << std::endl;
}

void GameState::update(const float& dt)
{
	// GameState updates
	this->updateMousePosition();
	this->updateInput(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	for (unsigned i = 0; i < this->playerVec->getsize(); i++)
		playerVec->at(i)->render(target);
}
