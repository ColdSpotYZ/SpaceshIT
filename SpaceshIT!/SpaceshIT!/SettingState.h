#pragma once
#include "State.h"
#include "GraphicsSettings.h"
#include "Gui.h"
class SettingState
	: public State
{
private:
    GraphicsSettings& gfxSettings;
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<char*, gui::Button*> buttons;
    std::map<char*, gui::DropDownList*> dropDownLists;

    sf::Text optionsText;

    Vector <sf::VideoMode> modes;


    void initVariables();
    void initKeybinds();
    void initBackground();
    void initFont();
    void initGUI();
    void initText();

public:
	SettingState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, std::map<string, int>* supportedKeys, Stack<State*>* states);
	virtual ~SettingState();

	// Accessors

	// Functions
    void endState();
    void updateInput(const float& dt);
    void updateGUI(const float& dt);
    void update(const float& dt);
    void renderGUI(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

