#pragma once

#include "GameState.h"
#include "Button.h"


class MainMenuState :
    public State
{
private:
    sf::RectangleShape background;
    sf::Font font;

    std::map<char *, Button*> buttons;


    void initFont();
    void initButtons();

public:
    MainMenuState(sf::RenderWindow* window, Stack<State*>* states);
    virtual ~MainMenuState();

    //Functions
    void endState();
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

