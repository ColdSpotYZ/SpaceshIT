#pragma once
#include "State.h"
#include "GraphicsSettings.h"
#include "Gui.h"
class CreditState
    : public State
{
private:
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<char*, gui::Button*> buttons;

    void initKeybinds();
    void initBackground();
    void initFont();
    void initGUI();

public:
    CreditState(sf::RenderWindow* window, Map<string, int>* supportedKeys, Stack<State*>* states);
    virtual ~CreditState();

    // Accessors

    // Functions
    void endState();
    void updateInput(const float& dt);
    void update(const float& dt);
    void updateGUI(const float& dt);
    void renderGUI(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

