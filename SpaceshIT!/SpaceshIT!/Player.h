#pragma once
#include "Actor.h"
#include "Bullet.h"
#include <map>

class Player :
    public Actor
{
private:

    int playerNum;
    int max_health = 100;
    int health;
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

    // Attack
    float attackCoolDown;
    float attackCoolDownMax = 10.f;

    // Functions
    void initVariables();
public:
    Player();
    Player(char* filename);
    virtual ~Player();

    // Accessors
    const int getHp() const;
    const int getHpMax() const;
    const int getPlayerNum() const;


    // Functions
    void move(const float dt, const float x, const float y);
    void takeDamage();
    void updateBullets();
    const bool canAttack();

    void updateAttack();
    void update(const float dt) override;
    void update(const float dt, std::map < std::string , int > keybinds);
    void render(sf::RenderTarget* target);
};

