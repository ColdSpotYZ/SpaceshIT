#pragma once
#include "State.h"
class MainMenuState :
    public State
{
private:
    sf::RectangleShape background;
    sf::Font font;
    void initFont();

public:
    MainMenuState(sf::RenderWindow* window);
    virtual ~MainMenuState();

    //Functions
    void endState();
    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

