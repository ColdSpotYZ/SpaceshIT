#include "Actor.h"

void Actor::initTexture()
{
}

void Actor::initSprite()
{
	this->sprite.setTexture(this->texture);
}

void Actor::initVariables()
{
}

Actor::Actor()
{
	this->initTexture();
	this->initSprite();
}

Actor::~Actor()
{
}

const sf::Vector2f& Actor::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Actor::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

sf::Sprite* Actor::getSprite()
{
	return &this->sprite;
}

sf::Texture* Actor::getTexture()
{
	return &this->texture;
}

void Actor::setPos(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Actor::setPos(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Actor::setSprite(sf::Sprite* sprite)
{
	this->sprite = *sprite;
}

void Actor::setTexture(sf::Texture* texture)
{
	this->texture = *texture;
}

void Actor::move(const float x, const float y)
{
}

void Actor::update()
{
}

void Actor::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
