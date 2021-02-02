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
		this->music.setVolume(15);
		this->music.play();
	}
}

void GameState::initFont()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
		throw("ERROR::MAINMENUSTATE::INITFONT::Failed to load menu font.");
}

void GameState::initPlayer()
{
	this->player1 = new Player((char*)"player1");
	this->player2 = new Player((char*)"player2");
	this->playerVec->push_back(this->player1);
	this->playerVec->push_back(this->player2);
}

void GameState::initGUI()
{
	// Game over text
	this->playerWin.setFont(this->font);
	this->playerWin.setCharacterSize(50);
	this->playerWin.setFillColor(sf::Color::White);
}

GameState::GameState(sf::RenderWindow* window, Stack<State*>* states)
	: State(window, states)
{
	initVariables();
	initFont();
	initPlayer();
	initGUI();
	initMusic();
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

void GameState::updateCollision()
{
	for (int i = 0; i < this->playerVec->getsize(); i++)
	{
		if (this->playerVec->at(i)->getBounds().left < 0.f)
		{
			this->playerVec->at(i)->setPos(0.f, this->playerVec->at(i)->getBounds().top);
		}
		else if (this->playerVec->at(i)->getBounds().left + this->playerVec->at(i)->getBounds().width > this->window->getSize().x)
		{
			this->playerVec->at(i)->setPos(this->window->getSize().x - this->playerVec->at(i)->getBounds().width, this->playerVec->at(i)->getBounds().top);
		}
		if (this->playerVec->at(i)->getBounds().top < 0.f)
		{
			this->playerVec->at(i)->setPos(this->playerVec->at(i)->getBounds().left, 0.f);
		}
		else if (this->playerVec->at(i)->getBounds().top + this->playerVec->at(i)->getBounds().height >= this->window->getSize().y)
		{
			this->playerVec->at(i)->setPos(this->playerVec->at(i)->getBounds().left, this->window->getSize().y - this->playerVec->at(i)->getBounds().height);
		}
	}
}

void GameState::update(const float& dt)
{
	// GameState updates
	this->updateCollision();
	this->updateMousePosition();
	this->updateInput(dt);
	
}

void GameState::render(sf::RenderTarget* target)
{
	for (unsigned i = 0; i < this->playerVec->getsize(); i++)
		playerVec->at(i)->render(target);
}
