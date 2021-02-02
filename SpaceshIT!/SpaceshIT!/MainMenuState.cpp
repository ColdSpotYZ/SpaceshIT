#include "MainMenuState.h"

void MainMenuState::initFont()
{
	if (!this->font.loadFromFile("Fonts/game.ttf"))
		throw("ERROR::MAINMENUSTATE::INITFONT::Failed to load menu font.");
}

void MainMenuState::initButtons()
{
	this->buttons[(char*)"GAME_STATE"] = new Button(sf::Vector2f(100, 100), sf::Vector2f(150, 50),
		&this->font, (char*)"PLAY",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	this->buttons[(char*)"SETTINGS"] = new Button(sf::Vector2f(100, 300), sf::Vector2f(150, 50),
		&this->font, (char*)"SETTINGS",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	this->buttons[(char*)"EXIT_STATE"] = new Button(sf::Vector2f(100, 500), sf::Vector2f(150, 50),
		&this->font, (char*)"QUIT",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, Stack<State*>* states)
	: State(window, states)
{
	this->initFont();
	this->initButtons();

	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color(27, 40, 69));
}

MainMenuState::~MainMenuState()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}
}

void MainMenuState::endState()
{
	// End game state
	this->quit = true;
}

void MainMenuState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void MainMenuState::updateButtons()
{
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}

	if (this->buttons[(char*)"GAME_STATE"]->isPressed())
		this->states->push(new GameState(this->window, this->states));
		

	if (this->buttons[(char*)"EXIT_STATE"]->isPressed())
		this->endState();
}

void MainMenuState::update(const float& dt)
{
	// MainMenuState updates
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
	
}

void MainMenuState::render(sf::RenderTarget* target)
{
	target->draw(this->background);
	this->renderButtons(target);
}
