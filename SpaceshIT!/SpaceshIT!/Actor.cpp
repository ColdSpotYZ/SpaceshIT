#include "Actor.h"

void Actor::initTexture(char* filename)
{
	std::stringstream s;
	s << "Assets/Textures/" << filename << ".png";
	if (!this->texture->loadFromFile(s.str()))
	{
		throw("ERROR::ACTOR::INITTEXTURE::Could not load texture file.");
	}
}

void Actor::initSprite(sf::Vector2f scale = sf::Vector2f(1.f, 1.f))
{
	// Set texture for sprite object
	this->sprite->setTexture(*this->texture);

	//Resize sprite
	this->sprite->scale(scale);
}

void Actor::initVariables()
{
	this->texture = new sf::Texture();
	this->sprite = new sf::Sprite();
	this->movementSpeed = 1000.f;
}

// PUBLIC

// Constructors

Actor::Actor()
{
	this->initVariables();
}

Actor::Actor(char* filename)
{
	this->initVariables();
	this->initTexture(filename);
	this->initSprite();
}

// Destructor

Actor::~Actor()
{
	delete this->sprite;
}

// Components

void Actor::createSprite(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite->setTexture(*this->texture);
}

// Functions

const sf::Vector2f& Actor::getPos() const
{
	return this->sprite->getPosition();
}

const sf::FloatRect Actor::getBounds() const
{
	return this->sprite->getGlobalBounds();
}

sf::Sprite* Actor::getSprite()
{
	return this->sprite;
}

sf::Texture* Actor::getTexture()
{
	return this->texture;
}

void Actor::setPos(const sf::Vector2f pos)
{
	this->sprite->setPosition(pos);
}

void Actor::setPos(const float x, const float y)
{
	this->sprite->setPosition(x, y);
}

void Actor::setSprite(sf::Sprite* sprite)
{
	this->sprite = sprite;
}

void Actor::setTexture(sf::Texture* texture)
{
	this->texture = texture;
}

void Actor::move(const float dt, const float x, const float y, float speed)
{
	if (this->sprite)
		this->sprite->move(speed * x * dt, speed * y * dt);
}

void Actor::render(sf::RenderTarget* target)
{
	if (this->sprite)
		target->draw(*this->sprite);
}
