#include "Menu.h"


void Menu::initFont()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
		std::cout << "Failed to load menu font." << std::endl;
}

Menu::Menu()
{
}

Menu::Menu(sf::Vector2f position, sf::Vector2f size, char* text)
{
	this->initFont();
	// Button
	this->button.setPosition(sf::Vector2f(position));
	this->button.setSize(size);
	this->button.setFillColor(sf::Color::Black);
	this->button.setOutlineColor(sf::Color::White);
	this->button.setOutlineThickness(5.f);

	// Text
	this->text = sf::Text(text, this->font);
	this->text.setCharacterSize(24);
	this->text.setPosition(
		sf::Vector2f(
		position.x + (size.x / 2) - (this->text.getCharacterSize()),
		position.y + (size.y / 2) - (this->text.getCharacterSize() / 2)
			)
		);
	this->text.setFillColor(sf::Color::White);
}

sf::RectangleShape Menu::Menu::getButton()
{
	return button;
}

sf::Text Menu::getText()
{
	return this->text;
}

bool Menu::isClicked(sf::Vector2f mousePos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->button.getGlobalBounds().contains(mousePos))
		{
			return true;
		}
	}
	return false;
}




