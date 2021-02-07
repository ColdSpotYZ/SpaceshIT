#include "stdafx.h"
#include "LeaderboardState.h"

void LeaderboardState::initVariables()
{
}

void LeaderboardState::initKeybinds()
{
	pair<std::string, int> temp = pair<std::string, int>{ "CLOSE", this->supportedKeys->at((char*)"Escape") };
	this->keybinds.insert(&temp);
}

void LeaderboardState::initBackground()
{
	this->background.setSize(sf::Vector2f((float)this->window->getSize().x, (float)this->window->getSize().y));
	if (!this->backgroundTexture.loadFromFile("Assets/Background/bg.png"))
		throw("ERROR::MAINMENUSTATE::INITBACKGROUND::Failed to load background image");
	this->background.setTexture(&this->backgroundTexture);
}

void LeaderboardState::initFont()
{
	if (!this->font.loadFromFile("Fonts/game.ttf"))
		throw("ERROR::MAINMENUSTATE::INITFONT::Failed to load menu font.");
}

void LeaderboardState::initGUI()
{
	this->buttons[(char*)"EXIT_STATE"] = new gui::Button(sf::Vector2f(100, 700), sf::Vector2f(150, 50),
		&this->font, (char*)"BACK",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	int score;
	// Read config(.ini) file
	std::ifstream player1_db("Config/DB/scores_player1.ini");
	if (player1_db.is_open())
	{
		while (player1_db >> score)
			player1Scores.push_back(score);
	}
	player1_db.close();
	// Read config(.ini) file
	std::ifstream player2_db("Config/DB/scores_player2.ini");
	if (player2_db.is_open())
	{
		while (player2_db >> score)
			player2Scores.push_back(score);
	}
	player2_db.close();

	player1Scores.sort();
	player1Scores.trim(player1Scores.getsize() - 10, player1Scores.getsize());
	player2Scores.sort();
	player2Scores.trim(player2Scores.getsize() - 10, player2Scores.getsize());

	this->Lists[(char*)"PLAYER 1"] = new gui::List(100, 100, 150, 50, font, player1Scores, player1Scores.getsize(), (char*)"Player 1");
	this->Lists[(char*)"PLAYER 2"] = new gui::List(100, 300, 150, 50, font, player2Scores, player2Scores.getsize(), (char*)"Player 2");
}

void LeaderboardState::initText()
{
}

LeaderboardState::LeaderboardState(sf::RenderWindow* window, Map<string, int>* supportedKeys, Stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initKeybinds();
	this->initBackground();
	this->initFont();
	this->initGUI();
	this->initText();
}

LeaderboardState::~LeaderboardState()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}

	auto i2 = this->Lists.begin();
	for (i2 = this->Lists.begin(); i2 != this->Lists.end(); ++i2)
	{
		delete i2->second;
	}
}


// Functions

void LeaderboardState::endState()
{
	// End game state
	this->quit = true;
}

void LeaderboardState::updateInput(const float& dt)
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();*/
}

void LeaderboardState::updateGUI(const float& dt)
{
	// Update all buttons
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}

	// Update dropdownlist
	for (auto& i : this->Lists)
	{
		i.second->update(this->mousePosView, dt);
	}

	if (this->buttons[(char*)"EXIT_STATE"]->isPressed() && this->getKeyTime())
		this->endState();

}

void LeaderboardState::update(const float& dt)
{
	// MainMenuState updates
	this->updateKeyTime(dt);
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateGUI(dt);
}

void LeaderboardState::renderGUI(sf::RenderTarget* target)
{
	// Render all buttons
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	// Render all list
	for (auto iter = this->Lists.rbegin(); iter != this->Lists.rend(); ++iter)
	{
		iter->second->render(target);
	}
}

void LeaderboardState::render(sf::RenderTarget* target)
{
	target->draw(this->background);
	this->renderGUI(target);
	target->draw(this->optionsText);
}
