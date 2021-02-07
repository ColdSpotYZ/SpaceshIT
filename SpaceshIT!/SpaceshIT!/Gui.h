#pragma once

enum buttonStates {BTN_IDLE = 0, BTN_HOVER = 1, BTN_ACTIVE = 2};

namespace gui
{
	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		Button(sf::Vector2f pos, sf::Vector2f size, sf::Font* font, char* text,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color outlineIdleColor = sf::Color::Transparent , sf::Color outlineHoverColor = sf::Color::Transparent, sf::Color outlineActiveColor = sf::Color::Transparent,
			short unsigned id = 0);
		virtual ~Button();

		// Accessors

		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		// Modifiers
		void setText(const std::string text);
		const void setId(const short unsigned& id);

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
		DropDownList(float x, float y, float width, float height, sf::Font& font, Vector<std::string> , unsigned noOfElements, unsigned default_index = 0);
		~DropDownList();

		// Accessors
		const unsigned short getActiveElementId() const;

		// Functions
		const bool getKeyTime();
		void updateKeyTime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget* target);
	};

	class List
	{
	private:
		float keyTime;
		float keyTimeMax;
		sf::Font& font;
		gui::Button* activeSelection;
		Vector <gui::Button*> list;
		bool showList;

	public:
		List(float x, float y, float width, float height, sf::Font& font, Vector<int> options, unsigned noOfElements, char* default_name);
		~List();

		// Functions
		const bool getKeyTime();
		void updateKeyTime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget* target);
	};
}