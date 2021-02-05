#include "stdafx.h"
#include "State.h"
#include "Game.h"
#include "Map.h"
#include <stack>

void Game::initVariables()
{
	this->window = nullptr;
	this->dt = 0.f;
}

void Game::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("Config/graphics.ini");
}

void Game::initWindow()
{
	
	if (this->gfxSettings.fullscreen)
		this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen, this->gfxSettings.contextSettings);
	else
		this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);

	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);

}

void Game::initKeys()
{

	std::ifstream ifs("Config/keys.ini");
	if (ifs.is_open())
	{
		std::string key;
		int key_code;

		while (ifs >> key >> key_code)
			this->supportedKeys[key] = key_code;
	}
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

void Game::initFonts()
{
	if (!this->mainFont.loadFromFile("Fonts/game.ttf"))
		throw("ERROR::GAME::INITFONTS::Failed to load font.");
}

void Game::initWorld()
{
	/*if (!this->worldBackgroundTexture.loadFromFile("Assets/Background/nebula/stars.png"))
		throw("ERROR::GAME::INITWORLD::Could not load background");
	this->worldBackgroundSprite.setTexture(this->worldBackgroundTexture);*/
}


Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initKeys();
	this->initStates();
	this->initWorld();
	this->initFonts();

}

Game::~Game()
{
	delete this->window;
	while (!this->states.isEmpty())
	{
		delete this->states.getTop();
		this->states.pop();
	}
}

/*###############
##	FUNCTIONS  ##	
###############*/

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void Game::updateDt()
{
	// Set this->dt variable with the time it takes per frame
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::endApp()
{
	this->window->close();
}

void Game::pollEvents()
{
	// TODO: Push onto stack and pop in render()
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::EventType::Closed:
			this->endApp();
			break;
		case sf::Event::EventType::GainedFocus:
			this->isFocus = true;
			break;
		case sf::Event::EventType::LostFocus:
			this->isFocus = false;
			break;
		}
	}
}

void Game::updateInput()
{
	// TODO: Push onto stack and pop in render()
	
}

void Game::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateWorld()
{
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackgroundSprite);
}

void Game::update()
{
	// Poll for events
	this->pollEvents();
	
	// Update inputs
	//if (this->gameStart && this->isFocus)
	//	this->updateInput();

	// Update from states
	if (!this->states.isEmpty())
	{
		if (this->isFocus)
			this->states.getTop()->update(this->dt);
		if (this->states.getTop()->getQuit())
		{
			this->states.getTop()->endState();
			delete this->states.getTop();
			this->states.pop();
		}
	}
	else
	{
		this->endApp();
	}

	// Update mouse position
	this->updateMousePosition();

	this->updateWorld();
}

void Game::render()
{
	/*
		- clear old frame
		- render objects
		- display frame in window
	*/
	this->window->clear();

	// World
	this->renderWorld();

	//Draw	

	// Render from states
	if (!this->states.isEmpty())
	{
		this->states.getTop()->render(this->window);
		if (this->states.getTop()->getQuit())
		{
			this->states.getTop()->endState();
			delete this->states.getTop();
			this->states.pop();
		}
	}
	else
	{
		this->endApp();
	}

		

	this->window->display();
}


void Game::run()
{
	while (this->getWindowIsOpen())
	{
		//Update Delta Time
		this->updateDt();
		//Update
		this->update();
		//Render
		this->render();

	}
}