#pragma once
#include "Actor.h"
class Player :
    public Actor
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    int health;
    int ammo;
    float speed;

    // Functions
    void initTexture(char*);
    void initSprite();
    void initVariables();
public:
    Player();
    Player(char*);
    virtual ~Player();

    // Accessors
    const sf::Vector2f& getPos() const;
    const sf::FloatRect getBounds() const;

    // Functions
    void setPos(const sf::Vector2f);
    void setPos(const float x, const float y);
    void move(const float x, const float y);
    void takeDamage();
    void shoot();

    void update(bool wasd);
    void render(sf::RenderTarget* target);
};

