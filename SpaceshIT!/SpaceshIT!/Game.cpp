#include "Game.h"


void Game::initVariables()
{
	this->window = nullptr;
	this->gameStart = false;
}

void Game::initWindow()
{
	this->videoMode.width = 1920;
	this->videoMode.height = 1080;

	this->window = new sf::RenderWindow(this->videoMode, "SpaceshIT!", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize /*| sf::Style::Fullscreen*/);
	this->window->setFramerateLimit(144);

}

void Game::initFonts()
{
	if (!this->mainFont.loadFromFile("Fonts/Dosis-Light.ttf"))
		std::cout << "Failed to load font." << std::endl;
}

void Game::initMenu()
{
	float button_x = 200.f;
	float button_y = 100.f;
	this->playButton = new Menu(
		sf::Vector2f(((this->window->getSize().x - button_x ) / 2 ), ((this->window->getSize().y - button_y ) / 2 )),
		sf::Vector2f(button_x, button_y),
		(char*)"PLAY"
	);
}


Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initMenu();
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
	}
}

void Game::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::update()
{
	// Poll for events
	this->pollEvents();

	// Update mouse position
	this->updateMousePosition();
}

void Game::render()
{
	/*
		- clear old frame
		- render objects
		- display frame in window
	*/
	this->window->clear();

	//Draw
	if (!this->gameStart)
	{
		if (!this->playButton->isClicked(this->mousePosView))
		{
			this->window->draw(this->playButton->getButton());
			this->window->draw(this->playButton->getText());
		}
		else
			this->gameStart = true;
	}
	

		

	this->window->display();
}
