#pragma once
#include "Actor.h"
#include "Bullet.h"
#include <map>

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
    float max_speed = 500.f;
    float speed;

    float rotation1 = 0.f;
    float rotateAmount1 = 0;
    float rotation2 = 0.f;
    float rotateAmount2 = 0;
    sf::Vector2f p1Velocity{ 0.f, 0.f };
    sf::Vector2f p2Velocity{ 0.f, 0.f };

    // Bullets
    Vector<Bullet*> bullets;

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
    void updateBullets();
    void updateGUI();

    void update(const float dt) override;
    void update(const float dt, std::map < std::string , int > keybinds, bool wasd);
    void render(sf::RenderTarget* target);
};

