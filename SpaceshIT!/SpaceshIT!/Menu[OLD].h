#pragma once
//
#include <iostream>
// SFML libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Menu
{
private:
	sf::RectangleShape button;
	sf::Text text;
	sf::Font font;
	void initFont();
	void initShapes(sf::Vector2f position, sf::Vector2f size, char* text);

public:
	Menu();
	Menu(sf::Vector2f position, sf::Vector2f size, char* text);

	//Functions
	void update();
	void render(sf::RenderTarget* target, sf::Vector2f mousePosView, bool& gameStart);
	sf::RectangleShape getButton();
	sf::Text getText();
	bool isClicked(sf::Vector2f mousePos);
};

