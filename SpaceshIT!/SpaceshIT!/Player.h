/*
Team member: Jason Chua & Lim Kai Xian
Group: CookieZ
studentID: S10195450H & S10195144H
*/
#pragma once
#include "Actor.h"
#include "Bullet.h"
#include "Asteroids.h"
#include "Map.h"
#include "Queue.h"
#include "xhash.h"

class Player :
    public Actor
{
private:

    int playerNum;
    int max_health = 100;
    int health;
    int ammo;
    int max_ammo = 20;
    float max_speed = 500.f;
    float speed;

    float rotation1 = 0.f;
    float rotateAmount1 = 0;
    float rotation2 = 0.f;
    float rotateAmount2 = 0;
    sf::Vector2f p1Velocity{ 0.f, 0.f };
    sf::Vector2f p2Velocity{ 0.f, 0.f };

    // UpdateLocation
    Queue PlayerLocations;

    // Bullets
    Vector<Bullet*> bullets;

    // Points
    int tickPoints = 1;
    int healthLostPoints = -500;
    int bulletUsedPoints = -20;
    int points = 0;

    // Attack
    float attackCoolDown;
    float attackCoolDownMax;

    // Functions
    void initVariables();
public:
    Player();
    Player(char* filename, sf::Vector2f pos);
    virtual ~Player();

    // Accessors
    const int getHp() const;
    const int getHpMax() const;
    const int getPlayerNum() const;
    const int getPoints() const;


    // Functions
    void move(const float dt, const float x, const float y);
    void takeDamage();
    void updateBullets();
    void Combat(Player* player, Player* player2);
    const bool canAttack();
    void updateAttack();
    void shoot();
    void heal();
    void restockammo();

    void queuePlayerLocation();
    void update(const float dt) override;
    void update(const float dt, Map<std::string, int> keybinds);
    void render(sf::RenderTarget* target);
};

