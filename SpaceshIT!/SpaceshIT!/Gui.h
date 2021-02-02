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
		const std::string& getText() const;

		// Modifiers
		void setText(const std::string text);

		// Functions
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget* target);
	};

	class DropDownList
	{
	private:
		float keyTime;
		float keyTimeMax;
		sf::Font& font;
		gui::Button* activeSelection;
		Vector <gui::Button*> list;
		bool showList;

	public:
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string options[], unsigned noOfElements, unsigned default_index = 0);
		~DropDownList();

		// Functions
		const bool getKeyTime();
		void updateKeyTime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget* target);
	};
}