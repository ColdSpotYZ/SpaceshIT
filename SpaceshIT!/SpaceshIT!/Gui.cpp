#include "stdafx.h"
#include "Gui.h"

gui::Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Font* font, char* text, 
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor,
	short unsigned id
)
{
	this->buttonState = BTN_IDLE;
	// Rectangle
	this->shape.setPosition(pos);
	this->shape.setSize(size);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outlineIdleColor);

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

	this->outlineIdleColor = outlineIdleColor;
	this->outlineHoverColor = outlineHoverColor;
	this->outlineActiveColor = outlineActiveColor;

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

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}

// Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

const void gui::Button::setId(const short unsigned& id)
{
	this->id = id;
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
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Blue);
		break;
	}
}

void gui::Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

gui::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, Vector <std::string> options, unsigned noOfElements, unsigned default_index)
	:font(font), showList(false), keyTimeMax(10.f), keyTime(0.f)
{
	this->activeSelection = new gui::Button(
		sf::Vector2f(x, y), sf::Vector2f(width, height),
		&this->font, (char*)options[default_index].c_str(),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 200)
	);
	for (unsigned i = 0; i < noOfElements; i++)
	{
		Button* temp = new gui::Button(
			sf::Vector2f(x, y + (i + 1) * height), sf::Vector2f(width, height),
			&this->font, (char*)options[i].c_str(),
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200),
			sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
			i
		);
		this->list.push_back(temp);
	}

}

gui::DropDownList::~DropDownList()
{
	delete this->activeSelection;
	for (auto& i : this->list)
		delete i;
}

const unsigned short gui::DropDownList::getActiveElementId() const
{
	return this->activeSelection->getId();
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
		{
			i->update(mousePos);
			if (i->isPressed() && this->getKeyTime())
			{
				this->showList = false;
				this->activeSelection->setText(i->getText());
				this->activeSelection->setId(i->getId());
			}
		}
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

gui::List::List(float x, float y, float width, float height, sf::Font& font, Vector<int> options, unsigned noOfElements, char* default_name)
	:font(font), showList(false), keyTimeMax(10.f), keyTime(0.f)
{
	this->activeSelection = new gui::Button(
		sf::Vector2f(x, y), sf::Vector2f(width, height),
		&this->font, default_name,
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 200)
	);
	for (unsigned i = 0; i < noOfElements; i++)
	{
		Button* temp = new gui::Button(
			sf::Vector2f(x, y + (noOfElements - i) * height), sf::Vector2f(width, height),
			&this->font, (char*)std::to_string(options[i]).c_str(),
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200),
			sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
			i
		);
		this->list.push_back(temp);
	}

}

gui::List::~List()
{
}

const bool gui::List::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

void gui::List::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 20.f * dt;
}

void gui::List::update(const sf::Vector2f& mousePos, const float& dt)
{
	this->updateKeyTime(dt);
	this->activeSelection->update(mousePos);

	if (this->activeSelection->isPressed() && this->getKeyTime())
	{
		this->showList = !this->showList;
	}
}

void gui::List::render(sf::RenderTarget* target)
{
	this->activeSelection->render(target);
	if (this->showList)
	{
		for (auto& i : this->list)
			i->render(target);
	}
}
