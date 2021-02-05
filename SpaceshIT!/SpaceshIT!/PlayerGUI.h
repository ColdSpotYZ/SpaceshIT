#pragma once

#include "Player.h"

class Player;

class PlayerGUI
{
private:
	Player* player;

	sf::Font font;
	// HP Bar
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	// Functions
	void initFonts();
	void initHpBar(sf::RenderWindow* window);

public:
	PlayerGUI(sf::RenderWindow* window, Player* player);
	virtual ~PlayerGUI();

	// Funtions
	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

