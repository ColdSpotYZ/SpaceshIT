#pragma once
#include "Actor.h"
class Player :
    public Actor
{
private:
    int max_health = 100;
    int health;
    int max_ammo = 20;
    int ammo;
    float max_speed = 1000.f;
    float speed;

    // Functions
    void initVariables();
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

    void update(const float dt) override;
    void update(const float dt, bool wasd);
};

