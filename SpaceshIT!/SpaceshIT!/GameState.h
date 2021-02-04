#pragma once
#include "State.h"
#include "Player.h"
#include "PauseMenu.h"

class GameState :
    public State
{
private:
    // Players
    Vector<Player*>* playerVec;
    Player* player1;
    Player* player2;

    // Background
    sf::Texture backgroundTexture;
    sf::RectangleShape background;

    // Font
    sf::Font font;

    // GUI
    sf::Text playerWin;
    PauseMenu* pauseMenu;

    // Game music
    sf::Music music;

    void initVariables();
    void initKeybinds();
    void initBackground();
    void initMusic();
    void initFont();
    void initPlayer();
    void initGUI();
    void initPauseMenu();

public:
    GameState(sf::RenderWindow* window, std::map<string, int>* supportedKeys, Stack<State*>* states);
    virtual ~GameState();

    //Functions
    void endState();
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updateCollision();
    void updatePauseMenuButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

