#pragma once

#include <iostream>
#include <sstream>

// SFML include
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


class Actor
{
protected:
	sf::Sprite* sprite;
	sf::Texture* texture;
	float movementSpeed;

	// Functions
	void initTexture(char*);
	void initSprite(sf::Vector2f);
	void initVariables();
public:
	Actor();
	Actor(char*);
	virtual ~Actor();

	// Component
	void createSprite(sf::Texture* texture);

	// Accessors
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	sf::Sprite* getSprite();
	sf::Texture* getTexture();

	// Setters
	void setPos(const sf::Vector2f);
	void setPos(const float x, const float y);
	void setSprite(sf::Sprite*);
	void setTexture(sf::Texture*);

	// Functions
	void move(const float dt, const float x, const float y, float speed);
	virtual void update(const float dt) = 0;
	virtual void render(sf::RenderTarget* target);
};

