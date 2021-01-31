#include "MainMenuState.h"

void MainMenuState::initFont()
{
	if (!this->font.loadFromFile("Fonts/game.ttf"))
		throw("ERROR::MAINMENUSTATE::INITFONT::Failed to load menu font.");
}

MainMenuState::MainMenuState(sf::RenderWindow* window)
	: State(window)
{
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color(27, 40, 69));
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::endState()
{
	// End game state
}

void MainMenuState::updateInput(const float& dt)
{
	this->checkForQuit();
}

void MainMenuState::update(const float& dt)
{
	// MainMenuState updates
	this->updateMousePosition();
	this->updateInput(dt);


}

void MainMenuState::render(sf::RenderTarget* target)
{
	target->draw(this->background);
}
