#pragma once
#include "State.h"
#include "Player.h"

class GameState :
    public State
{
private:
    // Players
    Vector<Player*>* playerVec;
    Player* player1;
    Player* player2;

    // Font
    sf::Font font;

    // GUI
    sf::Text playerWin;

    // Game music
    sf::Music music;

    void initVariables();
    void initMusic();
    void initFont();
    void initPlayer();
    void initGUI();

public:
    GameState(sf::RenderWindow* window, Stack<State*>* states);
    virtual ~GameState();

    //Functions
    void endState();
    void updateInput(const float& dt);
    void updateCollision();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

