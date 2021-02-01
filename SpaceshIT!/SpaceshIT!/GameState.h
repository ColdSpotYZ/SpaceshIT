#pragma once
#include "State.h"
#include "Player.h"

class GameState :
    public State
{
private:
    bool stateStart = false;
    // Players
    Vector<Player*>* playerVec;
    Player* player1;
    Player* player2;

    // Game music
    sf::Music music;

    void initVariables();
    void initMusic();
    void initPlayer();
public:
    GameState(sf::RenderWindow* window);
    virtual ~GameState();

    //Functions
    void endState();
    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

