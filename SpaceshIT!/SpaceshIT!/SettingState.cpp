#include "SettingState.h"

void SettingState::initVariables()
{
}

void SettingState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at((char*)"Escape");
}

void SettingState::initBackground()
{
	this->background.setSize(sf::Vector2f((float)this->window->getSize().x, (float)this->window->getSize().y));
	if (!this->backgroundTexture.loadFromFile("Assets/Background/bg.png"))
		throw("ERROR::MAINMENUSTATE::INITBACKGROUND::Failed to load background image");
	this->background.setTexture(&this->backgroundTexture);
}

void SettingState::initFont()
{
	if (!this->font.loadFromFile("Fonts/game.ttf"))
		throw("ERROR::MAINMENUSTATE::INITFONT::Failed to load menu font.");
}

void SettingState::initButtons()
{
	this->buttons[(char*)"EXIT_STATE"] = new gui::Button(sf::Vector2f(100, 700), sf::Vector2f(150, 50),
		&this->font, (char*)"QUIT",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
}

SettingState::SettingState(sf::RenderWindow* window, std::map<string, int>* supportedKeys, Stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initKeybinds();
	this->initBackground();
	this->initFont();
	this->initButtons();
}

SettingState::~SettingState()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}
}


// Functions

void SettingState::endState()
{
	// End game state
	this->quit = true;
}

void SettingState::updateInput(const float& dt)
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();*/
}

void SettingState::updateButtons()
{
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}

	if (this->buttons[(char*)"EXIT_STATE"]->isPressed())
		this->endState();
}

void SettingState::update(const float& dt)
{
	// MainMenuState updates
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();
}

void SettingState::renderButtons(sf::RenderTarget* target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

}

void SettingState::render(sf::RenderTarget* target)
{
	target->draw(this->background);
	this->renderButtons(target);
}
