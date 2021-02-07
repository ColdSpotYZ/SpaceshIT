#pragma once
#include "State.h"
#include "Gui.h"
class LeaderboardState
    : public State
{
private:
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<char*, gui::Button*> buttons;
    std::map<char*, gui::List*> Lists;

    sf::Text optionsText;

    Vector <int> player1Scores;
    Vector <int> player2Scores;


    void initVariables();
    void initKeybinds();
    void initBackground();
    void initFont();
    void initGUI();
    void initText();

public:
    LeaderboardState(sf::RenderWindow* window, Map<string, int>* supportedKeys, Stack<State*>* states);
    virtual ~LeaderboardState();

    // Accessors

    // Functions
    void endState();
    void updateInput(const float& dt);
    void updateGUI(const float& dt);
    void update(const float& dt);
    void renderGUI(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

