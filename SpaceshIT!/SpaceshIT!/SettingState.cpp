#include "stdafx.h"
#include "SettingState.h"

void SettingState::initVariables()
{
	for (auto i : sf::VideoMode::getFullscreenModes())
		this->modes.push_back(i);
}

void SettingState::initKeybinds()
{
	pair<std::string, int> temp = pair<std::string, int>{ "CLOSE", this->supportedKeys->at((char*)"Escape") };
	this->keybinds.insert(&temp);
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

void SettingState::initGUI()
{
	this->buttons[(char*)"EXIT_STATE"] = new gui::Button(sf::Vector2f(100, 780), sf::Vector2f(150, 50),
		&this->font, (char*)"BACK",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	this->buttons[(char*)"APPLY"] = new gui::Button(sf::Vector2f(100, 700), sf::Vector2f(150, 50),
		&this->font, (char*)"APPLY",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	Vector<std::string> modes_str;
	int count = 0;
	int def;
	for (auto& i : this->modes)
	{
		if (i.width == this->window->getSize().x && i.height == this->window->getSize().y)
			def = count;
		std::string temp = std::to_string(i.width) + "x" + std::to_string(i.height);
		modes_str.push_back(temp);
		count++;
	}
	this->dropDownLists[(char*)"RESOLUTIONS"] = new gui::DropDownList(100, 100, 150, 50, font, modes_str, modes_str.getsize(), def);

	Vector<std::string> yes_no;
	string yes = "Yes";
	string no = "No";
	yes_no.push_back(no);
	yes_no.push_back(yes);

	Vector<std::string> antialias_levels;
	string antialias_levels_1 = "1";
	string antialias_levels_2 = "2";
	string antialias_levels_4 = "4";
	string antialias_levels_8 = "8";
	string antialias_levels_16 = "16";
	antialias_levels.push_back(antialias_levels_1);
	antialias_levels.push_back(antialias_levels_2);
	antialias_levels.push_back(antialias_levels_4);
	antialias_levels.push_back(antialias_levels_8);
	antialias_levels.push_back(antialias_levels_16);



	this->dropDownLists[(char*)"FULLSCREEN"] = new gui::DropDownList(100, 250, 150, 50, font, yes_no, yes_no.getsize());

	this->dropDownLists[(char*)"VSYNC"] = new gui::DropDownList(100, 400, 150, 50, font, yes_no, yes_no.getsize());

	this->dropDownLists[(char*)"ANTIALIAS"] = new gui::DropDownList(100, 550, 150, 50, font, antialias_levels, antialias_levels.getsize());

}

void SettingState::initText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(300, 125));
	this->optionsText.setCharacterSize(24);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));
	this->optionsText.setString("Resolution \n\n\n\n\n\nFullscreen \n\n\n\n\n\nVsync \n\n\n\n\n\nAntialiasing (NOT WORKING) \n\n\n\n\n\n");
}

SettingState::SettingState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, Map<string, int>* supportedKeys, Stack<State*>* states)
	: State(window, supportedKeys, states), gfxSettings(gfxSettings)
{
	this->initVariables();
	this->initKeybinds();
	this->initBackground();
	this->initFont();
	this->initGUI();
	this->initText();
}

SettingState::~SettingState()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}

	auto i2 = this->dropDownLists.begin();
	for (i2 = this->dropDownLists.begin(); i2 != this->dropDownLists.end(); ++i2)
	{
		delete i2->second;
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

void SettingState::updateGUI(const float& dt)
{
	// Update all buttons
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}

	// Update dropdownlist
	for (auto& i : this->dropDownLists)
	{
		i.second->update(this->mousePosView, dt);
	}

	if (this->buttons[(char*)"EXIT_STATE"]->isPressed() && this->getKeyTime())
		this->endState();

	if (this->buttons[(char*)"APPLY"]->isPressed() && this->getKeyTime())
	{
		this->gfxSettings.resolution = this->modes[this->dropDownLists[(char*)"RESOLUTIONS"]->getActiveElementId()];
		this->gfxSettings.fullscreen = this->dropDownLists[(char*)"FULLSCREEN"]->getActiveElementId();
		this->gfxSettings.verticalSync = this->dropDownLists[(char*)"VSYNC"]->getActiveElementId();
		this->gfxSettings.contextSettings.antialiasingLevel = pow(2, this->dropDownLists[(char*)"ANTIALIAS"]->getActiveElementId());
		if (this->gfxSettings.fullscreen)
			this->window->create(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen, this->gfxSettings.contextSettings);
		else
			this->window->create(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);
	}

}

void SettingState::update(const float& dt)
{
	this->background.setSize(sf::Vector2f((float)this->window->getSize().x, (float)this->window->getSize().y));
	// MainMenuState updates
	this->updateKeyTime(dt);
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateGUI(dt);
}

void SettingState::renderGUI(sf::RenderTarget* target)
{
	// Render all buttons
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	// Render all dropdownlist
	for (auto iter = this->dropDownLists.rbegin(); iter != this->dropDownLists.rend(); ++iter)
	{
		iter->second->render(target);
	}
}

void SettingState::render(sf::RenderTarget* target)
{
	target->draw(this->background);
	target->draw(this->optionsText);
	this->renderGUI(target);
	
}
