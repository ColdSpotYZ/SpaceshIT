/*
Team member: Lim Kai Xian
Group: CookieZ
studentID: S10195450H
*/

#include "stdafx.h"
#include "CreditState.h"

void CreditState::initFont()
{
	if (!this->font.loadFromFile("Fonts/game.ttf"))
		throw("ERROR::MAINMENUSTATE::INITFONT::Failed to load menu font.");
}

void CreditState::initKeybinds()
{
	pair<std::string, int> temp = pair<std::string, int>{ "CLOSE", this->supportedKeys->at((char*)"Escape") };
	this->keybinds.insert(&temp);
}

CreditState::CreditState(sf::RenderWindow* window, Map<string, int>* supportedKeys, Stack<State*>* states) 
	: State(window, supportedKeys, states)
{
	this->initFont();
	this->initKeybinds();
	this->initBackground();
	this->initGUI();
}

CreditState::~CreditState()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}
}

void CreditState::initBackground()
{
	this->background.setSize(sf::Vector2f((float)this->window->getSize().x, (float)this->window->getSize().y));
	if (!this->backgroundTexture.loadFromFile("Assets/Background/credit.png"))
		throw("ERROR::MAINMENUSTATE::INITBACKGROUND::Failed to load background image");
	this->background.setTexture(&this->backgroundTexture);
}

void CreditState::initGUI()
{
	this->buttons[(char*)"LEADERBOARD"] = new gui::Button(sf::Vector2f(300, 700), sf::Vector2f(150, 50),
		&this->font, (char*)"LEADERBOARD",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	this->buttons[(char*)"EXIT_STATE"] = new gui::Button(sf::Vector2f(100, 700), sf::Vector2f(150, 50),
		&this->font, (char*)"BACK",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
}

// Functions

void CreditState::endState()
{
	// End game state
	this->quit = true;
}

void CreditState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
		this->endState();
}

void CreditState::updateGUI(const float& dt)
{
	// Update all buttons
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}

	if (this->buttons[(char*)"LEADERBOARD"]->isPressed() && this->getKeyTime())
		this->states->push(new LeaderboardState(this->window, this->supportedKeys, this->states));

	if (this->buttons[(char*)"EXIT_STATE"]->isPressed() && this->getKeyTime())
		this->endState();
}

void CreditState::update(const float& dt)
{
	// MainMenuState updates
	this->updateKeyTime(dt);
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateGUI(dt);
}

void CreditState::renderGUI(sf::RenderTarget* target)
{
	// Render all buttons
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void CreditState::render(sf::RenderTarget* target)
{
	target->draw(this->background);
	this->renderGUI(target);
}
