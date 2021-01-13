#include "Game.h"



void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.width = 1920;
	this->videoMode.height = 1080;
	

	this->window = new sf::RenderWindow(this->videoMode, "SpaceshIT!", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize /*| sf::Style::Fullscreen*/);
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::EventType::Closed:
			this->window->close();
			break;
		case sf::Event::EventType::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::update()
{
	this->pollEvents();
}

void Game::render()
{
	/*
		- clear old frame
		- render objects
		- display frame in window
	*/
	this->window->clear(sf::Color::Cyan);

	//Draw
	//sf::Texture texture;
	//if (!texture.loadFromFile(""))
	//	throw "Unable to find texture";
	//sf::Sprite sprite(texture);

	this->window->display();
}
