#pragma once
#include "State.h"
#include "Gui.h"
class SettingState
	: public State
{
private:
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<char*, gui::Button*> buttons;

    gui::DropDownList* ddl;


    void initVariables();
    void initKeybinds();
    void initBackground();
    void initFont();
    void initButtons();

public:
	SettingState(sf::RenderWindow* window, std::map<string, int>* supportedKeys, Stack<State*>* states);
	virtual ~SettingState();

	// Accessors

	// Functions
    void endState();
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

