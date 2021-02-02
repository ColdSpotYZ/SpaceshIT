#include "Gui.h"

gui::Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Font* font, char* text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;
	// Rectangle
	this->shape.setPosition(pos);
	this->shape.setSize(size);

	// Text
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setCharacterSize(20);
	this->text.setPosition(
		sf::Vector2f(
			pos.x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
			pos.y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f
		)
	);
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
}

gui::Button::~Button()
{
}


const bool gui::Button::isPressed() const
{
	return (this->buttonState == BTN_ACTIVE) ? true : false;
}

void gui::Button::update(const sf::Vector2f& mousePos)
{
	// Check idle, hover or active
	this->buttonState = BTN_IDLE;
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->buttonState = BTN_ACTIVE;
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Blue);
		break;
	}
}

void gui::Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

void gui::DropDownList::update(const sf::Vector2f& mousePos)
{
}

void gui::DropDownList::render(sf::RenderTarget* target)
{
}
