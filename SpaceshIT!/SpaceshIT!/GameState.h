#pragma once
#include "State.h"
#include "Player.h"

class GameState :
    public State
{
private:
    Vector<Player*>* playerVec;
    Player* player1;
    Player* player2;
    void initVariables();
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

