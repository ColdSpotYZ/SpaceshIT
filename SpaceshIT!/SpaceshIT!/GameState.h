/*
Team member: Jason Chua
Group: CookieZ
studentID: S10195450H
*/
#pragma once
#include "State.h"
#include "Player.h"
#include "PauseMenu.h"
#include "PlayerGUI.h"
#include "Map.h"
#include "Bullet.h"
#include "Asteroids.h"
#include "BulletPack.h"
#include "HealthPack.h"

class GameState :
    public State
{
private:
    bool endGame = false;
    // Players
    Vector<Player*>* playerVec;
    Player* player1;
    Player* player2;
    Vector<PlayerGUI*> playerGUIs;

    // Asteroids
    float spawnTimerAsteroids;
    float spawnTimerAsteroidsMax = 50.f;
    Vector<Asteroids*> Asteroid_s;

    // Bullet Pack
    float SpawnTimerBulletPack;
    float spawnTimerBulletPackMax = 70.f;
    Vector<BulletPack*> BulletPacks;

    // Health Pack
    float spawnTimerHealthPack;
    float spawnTimerHealthPackMax = 100.f;
    Vector<HealthPack*> HealthPacks;

    // Points
    Vector<int> playerPoints;

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
    void initAsteroid();
    void initPacks();
    void initGUI();
    void initPauseMenu();
    void initPlayerGUI();

public:
    GameState(sf::RenderWindow* window, Map<string, int>* supportedKeys, Stack<State*>* states);
    virtual ~GameState();

    //Functions
    void endState();
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePlayerGUI(const float& dt);
    void updateAsteroid();
    void updatePacks();
    void collectPacks(Player* player);
    void updateCollision();
    void AsteroidsDamage(Player* player);
    void updatePauseMenuButtons();
    void updateGameStateEnd();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

