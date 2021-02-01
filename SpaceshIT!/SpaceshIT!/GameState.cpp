#include "GameState.h"

void GameState::initVariables()
{
	this->playerVec = new Vector<Player*>;
}

void GameState::initMusic()
{
	if (!this->music.openFromFile("Assets/Audio/theme.wav"))
		throw("ERROR::GAMESTATE::INITMUSIC::Unable to load music");
	else
	{
		this->music.setLoop(true);
		this->music.setVolume(25);
		this->music.play();
	}
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
	for (unsigned i = 0; i < this->playerVec->getsize(); i++)
	{
		this->playerVec->at(i)->update(dt, !i);
	}
}

void GameState::update(const float& dt)
{
	//Run once
	if (!this->stateStart)
	{
		initMusic();
		this->stateStart = true;
	}
		
	// GameState updates
	this->updateMousePosition();
	this->updateInput(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	for (unsigned i = 0; i < this->playerVec->getsize(); i++)
		playerVec->at(i)->render(target);
}
