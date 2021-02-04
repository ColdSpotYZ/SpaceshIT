#include "stdafx.h"
#include "PauseMenu.h"

// Constructor

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	:font(font)
{
	// Background
	this->background.setSize(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	// Container
	this->container.setSize(sf::Vector2f(
		(float)window.getSize().x / 4.f,
		(float)window.getSize().y - 60.f
	));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(sf::Vector2f(
		(float)window.getSize().x / 2.f - this->container.getSize().x / 2.f, // Center of X of screen
		30.f
		));

	// Text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(50);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(sf::Vector2f(
		this->container.getPosition().x + (this->container.getSize().x / 2.f) - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20.f
	));
}

// Destructor

PauseMenu::~PauseMenu()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}


// Functions

const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 150;
	float height = 50;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
	this->buttons[key] = new gui::Button(sf::Vector2f(x, y), sf::Vector2f(width, height),
		&this->font, (char*)text.c_str(),
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto& i : this->buttons)
		i.second->update(mousePos);
}

void PauseMenu::render(sf::RenderTarget* target)
{
	target->draw(background);
	target->draw(container);
	
	for (auto& i : this->buttons)
		i.second->render(target);

	target->draw(menuText);
}
