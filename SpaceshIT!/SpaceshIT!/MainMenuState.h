#pragma once

#include "GameState.h"
#include "GraphicsSettings.h"
#include "SettingState.h"
#include "Gui.h"


class MainMenuState :
    public State
{
private:
    GraphicsSettings& gfxSettings;
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<char *, gui::Button*> buttons;

    
    void initVariables();
    void initKeybinds();
    void initBackground();
    void initFont();
    void initButtons();

public:
    MainMenuState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, Map<string, int>* supportedKeys, Stack<State*>* states);
    virtual ~MainMenuState();

    // Functions
    void endState();
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

