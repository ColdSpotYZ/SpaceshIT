#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet() 
{
	this->state = true;
};

Bullet::Bullet(float pos_x, float pos_y, float dir_X, float dir_Y, float speed)
{
	this->texture.loadFromFile("Assets/Textures/bullet.png");
	this->state = true;
	this->shape.setTexture(this->texture);
	this->shape.setPosition(pos_x, pos_y);
	this->direction.x = dir_X;
	this->direction.y = dir_Y;
	this->movementSpeed = speed;
}

Bullet::~Bullet()
{
	// Empty
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
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

