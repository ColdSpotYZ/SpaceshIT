#include "stdafx.h"
#include "GameState.h"

void GameState::initVariables()
{
	this->playerVec = new Vector<Player*>;
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keys.ini");
	if (ifs.is_open())
	{
		std::string key;
		string key_code_map;

		while (ifs >> key >> key_code_map)
			this->keybinds[key] = this->supportedKeys->at(key_code_map);
	}
}

void GameState::initBackground()
{
	this->background.setSize(sf::Vector2f((float)this->window->getSize().x, (float)this->window->getSize().y));
	if (!this->backgroundTexture.loadFromFile("Assets/Background/game.png"))
		throw("ERROR::MAINMENUSTATE::INITBACKGROUND::Failed to load background image");
	this->background.setTexture(&this->backgroundTexture);
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

void GameState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);
	this->pauseMenu->addButton("EXIT_STATE", 700.f , "QUIT");
}

GameState::GameState(sf::RenderWindow* window, std::map<string, int>* supportedKeys, Stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initVariables();
	initKeybinds();
	initBackground();
	initFont();
	initPauseMenu();
	initPlayer();
	initGUI();
	initMusic();
}

GameState::~GameState()
{
	this->playerVec->~Vector();
	delete this->pauseMenu;
}

void GameState::endState()
{
	// End game state
	this->quit = true;
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->paused)
		{
			this->pauseState();
			this->music.pause();
		}
		else
		{
			this->unpauseState();
			this->music.play();
		}
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	for (unsigned i = 0; i < this->playerVec->getsize(); i++)
	{
		this->playerVec->at(i)->update(dt, this->keybinds, !i);
	}
}

void GameState::updateCollision()
{
	for (int i = 0; i < this->playerVec->getsize(); i++)
	{
		if (this->playerVec->at(i)->getBounds().left < 0.f)
		{
			this->playerVec->at(i)->setPos(0.f + this->playerVec->at(i)->getBounds().width / 2.f, this->playerVec->at(i)->getBounds().top + this->playerVec->at(i)->getBounds().height / 2.f);
		}
		else if (this->playerVec->at(i)->getBounds().left + this->playerVec->at(i)->getBounds().width > this->window->getSize().x)
		{
			this->playerVec->at(i)->setPos(this->window->getSize().x - this->playerVec->at(i)->getBounds().width / 2.f, this->playerVec->at(i)->getBounds().top + this->playerVec->at(i)->getBounds().height / 2.f);
		}
		if (this->playerVec->at(i)->getBounds().top < 0.f)
		{
			this->playerVec->at(i)->setPos(this->playerVec->at(i)->getBounds().left + this->playerVec->at(i)->getBounds().width / 2.f, 0.f + this->playerVec->at(i)->getBounds().height / 2.f);
		}
		else if (this->playerVec->at(i)->getBounds().top + this->playerVec->at(i)->getBounds().height >= this->window->getSize().y)
		{
			this->playerVec->at(i)->setPos(this->playerVec->at(i)->getBounds().left + this->playerVec->at(i)->getBounds().width / 2.f, this->window->getSize().y - this->playerVec->at(i)->getBounds().height / 2.f);
		}
	}
}

void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("EXIT_STATE"))
		this->endState();
}

void GameState::update(const float& dt)
{
	// GameState updates
	this->updateMousePosition();
	this->updateKeyTime(dt);
	this->updateInput(dt);
	if (!this->paused)
	{
		this->updateCollision();	
		this->updatePlayerInput(dt);
	}
	else
	{
		this->pauseMenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
	
}

void GameState::render(sf::RenderTarget* target)
{
	target->draw(this->background);
	for (unsigned i = 0; i < this->playerVec->getsize(); i++)
		playerVec->at(i)->render(target);
	if (this->paused)
	{

		this->pauseMenu->render(target);
	}
}
