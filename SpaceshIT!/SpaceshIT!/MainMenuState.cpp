#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initVariables()
{
}

void MainMenuState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at((char*)"Escape");
}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f((float)this->window->getSize().x, (float)this->window->getSize().y));
	if (!this->backgroundTexture.loadFromFile("Assets/Background/bg.png"))
		throw("ERROR::MAINMENUSTATE::INITBACKGROUND::Failed to load background image");
	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFont()
{
	if (!this->font.loadFromFile("Fonts/game.ttf"))
		throw("ERROR::MAINMENUSTATE::INITFONT::Failed to load menu font.");
}

void MainMenuState::initButtons()
{
	this->buttons[(char*)"GAME_STATE"] = new gui::Button(sf::Vector2f(100, 100), sf::Vector2f(150, 50),
		&this->font, (char*)"PLAY",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	this->buttons[(char*)"SETTINGS"] = new gui::Button(sf::Vector2f(100, 300), sf::Vector2f(150, 50),
		&this->font, (char*)"SETTINGS",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	this->buttons[(char*)"CREDITS"] = new gui::Button(sf::Vector2f(100, 500), sf::Vector2f(150, 50),
		&this->font, (char*)"CREDITS",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));


	this->buttons[(char*)"EXIT_STATE"] = new gui::Button(sf::Vector2f(100, 700), sf::Vector2f(150, 50),
		&this->font, (char*)"QUIT",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, Map<string, int>* supportedKeys, Stack<State*>* states)
	: State(window, supportedKeys, states), gfxSettings(gfxSettings)
{
	this->initVariables();
	this->initKeybinds();
	this->initBackground();
	this->initFont();
	this->initButtons();
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
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();*/
}

void MainMenuState::updateButtons()
{
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}

	if (this->buttons[(char*)"GAME_STATE"]->isPressed() && this->getKeyTime())
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));

	//if (this->buttons[(char*)"CREDITS"]->isPressed())
	//	this->states->push(new CreditState(this->window, this->supportedKeys, this->states))
		
	if (this->buttons[(char*)"SETTINGS"]->isPressed() && this->getKeyTime())
		this->states->push(new SettingState(this->window, this->gfxSettings, this->supportedKeys, this->states));

	if (this->buttons[(char*)"EXIT_STATE"]->isPressed() && this->getKeyTime())
		this->endState();
}

void MainMenuState::update(const float& dt)
{
	// MainMenuState updates
	this->updateKeyTime(dt);
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
