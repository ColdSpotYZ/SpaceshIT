#include "Game.h"


void Game::initVariables()
{
	this->window = nullptr;
	this->gameStart = false;
	Player temp = Player();
	this->playerVec = new Vector<Player*>;
}

void Game::initWindow()
{
	this->videoMode.width = 1600;
	this->videoMode.height = 900;

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
	this->playerVec->push_back(this->player1);
	this->playerVec->push_back(this->player2);
}

void Game::initGUI()
{
	// Game over text
	this->playerWin.setFont(this->mainFont);
	this->playerWin.setCharacterSize(50);
	this->playerWin.setFillColor(sf::Color::White);

	// Player1 Health Bar
	this->player1HpBar.setSize(sf::Vector2f(this->player1->getBounds().width, 10.f));
	this->player1HpBar.setFillColor(sf::Color::Red);
	this->player1HpBar.setPosition(sf::Vector2f(this->player1->getPos().x, this->player1->getPos().y - (this->player1->getBounds().height / 4)));

	this->player1HpBarBack = this->player1HpBar;
	this->player1HpBarBack.setFillColor(sf::Color(30, 30, 30, 240));

	// Player2 Health Bar
	this->player2HpBar.setSize(sf::Vector2f(this->player2->getBounds().width, 10.f));
	this->player2HpBar.setFillColor(sf::Color::Red);
	this->player2HpBar.setPosition(sf::Vector2f(this->player2->getPos().x, this->player2->getPos().y - (this->player2->getBounds().height / 4)));

	this->player2HpBarBack = this->player2HpBar;
	this->player2HpBarBack.setFillColor(sf::Color(33, 33, 33, 240));
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
	this->initGUI();
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
	// Something else

	// Players health bar
	
	this->player1HpBar.setSize(sf::Vector2f(this->player1->getBounds().width * (static_cast<float>(this->player1->getHp()) / this->player1->getHpMax()), this->player1HpBar.getSize().y));
	this->player1HpBar.setPosition(sf::Vector2f(this->player1->getPos().x, this->player1->getPos().y - (this->player1->getBounds().height / 4)));
	this->player1HpBarBack.setPosition(sf::Vector2f(this->player1->getPos().x, this->player1->getPos().y - (this->player1->getBounds().height / 4)));
	this->player2HpBar.setSize(sf::Vector2f(this->player2->getBounds().width * (static_cast<float>(this->player2->getHp()) / this->player2->getHpMax()), this->player2HpBar.getSize().y));
	this->player2HpBar.setPosition(sf::Vector2f(this->player2->getPos().x, this->player2->getPos().y - (this->player2->getBounds().height / 4)));
	this->player2HpBarBack.setPosition(sf::Vector2f(this->player2->getPos().x, this->player2->getPos().y - (this->player2->getBounds().height / 4)));
}

void Game::updateWorld()
{
}

void Game::updateCollision()
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
	this->updateGUI();

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
		this->window->draw(this->player1HpBarBack);
		this->window->draw(this->player1HpBar);
		this->window->draw(this->player2HpBarBack);
		this->window->draw(this->player2HpBar);
	}

		

	this->window->display();
}
