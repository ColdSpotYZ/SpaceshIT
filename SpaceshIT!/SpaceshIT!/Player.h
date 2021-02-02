#pragma once
#include "Actor.h"
class Player :
    public Actor
{
private:
    // HP Bar
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;

    int max_health = 100;
    int health;
    int max_ammo = 20;
    int ammo;
    float max_speed = 1000.f;
    float speed;

    // Functions
    void initVariables();
    void initGUI();
public:
    Player();
    Player(char* filename);
    virtual ~Player();

    // Accessors
    const int getHp() const;
    const int getHpMax() const;


    // Functions
    void move(const float dt, const float x, const float y);
    void takeDamage();
    void shoot();
    void updateGUI();

    void update(const float dt) override;
    void update(const float dt, std::map < std::string , int > keybinds, bool wasd);
    void render(sf::RenderTarget* target);
};

