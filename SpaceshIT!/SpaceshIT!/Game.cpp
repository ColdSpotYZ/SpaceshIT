#include "Game.h"


void Game::initVariables()
{
	this->window = nullptr;
	this->gameStart = false;
	Player temp = Player();
	this->playerVec = new Vector<Player>;
	this->temp = new std::vector<Player>;
}

void Game::initWindow()
{
	this->videoMode.width = 1920;
	this->videoMode.height = 1080;

	this->window = new sf::RenderWindow(this->videoMode, "SpaceshIT!", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize /*| sf::Style::Fullscreen*/);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);

}

void Game::initFonts()
{
	if (!this->mainFont.loadFromFile("Fonts/Dosis-Light.ttf"))
		std::cout << "Failed to load font." << std::endl;
}

void Game::initWorld()
{
	if (!this->worldBackgroundTexture.loadFromFile("Assets/Background/nebula/nebula01.png"))
		std::cout << "ERROR::GAME::Could not load background" << std::endl;
	this->worldBackgroundSprite.setTexture(this->worldBackgroundTexture);
}

void Game::initPlayer()
{
	this->player1 = new Player((char*)"player1");
	this->player2 = new Player((char*)"player2");
	this->playerVec->push_back(*this->player1);
	this->playerVec->push_back(*this->player2);

	this->temp->push_back(*this->player1);
	this->temp->push_back(*this->player2);
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
	this->initWorld();
	this->initFonts();
	this->initMenu();
	this->initPlayer();
}

Game::~Game()
{
	delete this->window;
	delete this->playButton;
	delete this->player1;
	delete this->player2;
}

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	// TODO: Push onto stack and pop in render()
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

void Game::updateInput()
{
	// TODO: Push onto stack and pop in render()
	this->player1->update(true);
	this->player2->update(false);
}

void Game::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateGUI()
{
}

void Game::updateWorld()
{
}

void Game::updateCollision()
{
	// NOT WORKING
	/*for (int i = 0; i < this->playerVec->getsize(); i++)
	{
		std::cout << this->playerVec->at(0).getBounds().left << std::endl;
		if (this->playerVec->operator[](i).getBounds().left < 0.f)
		{
			this->playerVec->at(i).setPos(0.f, this->playerVec->at(i).getBounds().top);
		}
	}*/

	// WORKING CODE
	if (this->player1->getBounds().left < 0.f)
	{
		this->player1->setPos(0.f, this->player1->getBounds().top);
	}
	//

	//TESTING
	for (int i = 0; i < this->temp->size(); i++)
	{
		std::cout << this->temp->at(i).getBounds().left << std::endl;
		if (this->temp->at(i).getBounds().left < 0.f)
		{
			this->temp->at(i).setPos(0.f, this->temp->at(i).getBounds().top);
		}
	}
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
	if (this->gameStart)
		this->updateInput();

	this->updateCollision();

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
	if (!this->gameStart)
		this->playButton->render(this->window, this->mousePosView, this->gameStart);
	else
	{
		this->player1->render(this->window);
		this->player2->render(this->window);
	}

		

	this->window->display();
}
