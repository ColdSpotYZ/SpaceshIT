#pragma once

#include "Vector.h"

// SFML include
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

enum buttonStates {BTN_IDLE = 0, BTN_HOVER = 1, BTN_ACTIVE = 2};

namespace gui
{
	class Button
	{
	private:
		short unsigned buttonState;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

	public:
		Button(sf::Vector2f pos, sf::Vector2f size, sf::Font* font, char* text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
		virtual ~Button();

		// Accessors

		const bool isPressed() const;

		// Functions

		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget* target);
	};

	class DropDownList
	{
	private:
		sf::RectangleShape activeSelection;
		Vector<sf::RectangleShape> list;

	public:
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget* target);
	};
}