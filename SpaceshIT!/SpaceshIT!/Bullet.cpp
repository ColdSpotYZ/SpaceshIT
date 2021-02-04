#include "stdafx.h"
#include "Bullet.h"

void Bullet::InitVairables()
{
	this->movementSpeed = this->movementSpeed;
	this->state = this->state;
}

Bullet::Bullet() 
{
	this->initVariables();
};

Bullet::Bullet(sf::Texture& texture, float dir_X, float dir_Y, float speed)
{
	this->shape.setTexture(texture);
	this->direction.x = dir_X;
	this->direction.y = dir_Y;
	this->movementSpeed = speed;
}

Bullet::~Bullet()
{
	// Empty
}

void Bullet::update()
{
	this->shape.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

bool Bullet::getState()
{
	return this->state;
}

void Bullet::changeState(bool state)
{
	this->state = state;
}

void Bullet::move(const float dt, const float x, const float y)
{
	this->sprite->move(this->movementSpeed * x * dt, this->movementSpeed * y * dt);
}

