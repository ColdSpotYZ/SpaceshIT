#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
		throw("ERROR::PLAYERGUI::INITFONT::Failed to load menu font.");
}

void PlayerGUI::initHpBar(sf::RenderWindow* window)
{
	if (player->getPlayerNum() == 1)
	{
		this->playerHpBar.setSize(sf::Vector2f(200.f, 10.f));
		this->playerHpBar.setFillColor(sf::Color::Blue);
		this->playerHpBar.setPosition(sf::Vector2f(0, 0));

		this->playerHpBarBack = this->playerHpBar;
		this->playerHpBarBack.setFillColor(sf::Color(30, 30, 30, 240));
	}
	else
	{
		this->playerHpBar.setSize(sf::Vector2f(200.f, 10.f));
		this->playerHpBar.setFillColor(sf::Color::Red);
		this->playerHpBar.setPosition(sf::Vector2f(window->getSize().x - 200.f, 0.f));

		this->playerHpBarBack = this->playerHpBar;
		this->playerHpBarBack.setFillColor(sf::Color(30, 30, 30, 240));
	}
}

PlayerGUI::PlayerGUI(sf::RenderWindow* window, Player* player)
{
	this->player = player;
	this->initHpBar(window);
}

PlayerGUI::~PlayerGUI()
{
}

void PlayerGUI::update(const float& dt)
{
	this->playerHpBar.setSize(sf::Vector2f(200.f * (static_cast<float>(this->player->getHp()) / this->player->getHpMax()), this->playerHpBar.getSize().y));
}

void PlayerGUI::render(sf::RenderTarget* target)
{
	target->draw(this->playerHpBarBack);
	target->draw(this->playerHpBar);
}
