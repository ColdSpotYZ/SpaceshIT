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

// Accessors
const bool gui::Button::isPressed() const
{
	return (this->buttonState == BTN_ACTIVE) ? true : false;
}

const std::string& gui::Button::getText() const
{
	return this->text.getString();
}

// Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

// Functions
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

gui::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, std::string options[], unsigned noOfElements, unsigned default_index)
	:font(font), showList(false), keyTimeMax(10.f), keyTime(0.f)
{
	for (unsigned i = 0; i < noOfElements; i++)
	{
		Button* temp = new gui::Button(
			sf::Vector2f(x, y + i * height), sf::Vector2f(width, height),
			&this->font, (char*)options[i].c_str(),
			sf::Color(70, 70, 70, 200),
			sf::Color(150, 150, 150, 255),
			sf::Color(20, 20, 20, 200)
		);
		this->list.push_back(temp);
	}

	this->activeSelection = new Button(*this->list[default_index]);
}

gui::DropDownList::~DropDownList()
{
	delete this->activeSelection;
	for (auto& i : this->list)
		delete i;
}

// Accessors
const bool gui::DropDownList::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

// Functions
void gui::DropDownList::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 20.f * dt;
}

void gui::DropDownList::update(const sf::Vector2f& mousePos, const float& dt)
{
	this->updateKeyTime(dt);
	this->activeSelection->update(mousePos);

	if (this->activeSelection->isPressed() && this->getKeyTime())
	{
		this->showList = !this->showList;
	}

	if (this->showList)
	{
		for (auto& i : this->list)
			i->update(mousePos);
	}
}

void gui::DropDownList::render(sf::RenderTarget* target)
{
	this->activeSelection->render(target);
	if (this->showList)
	{
		for (auto& i : this->list)
			i->render(target);
	}
}
