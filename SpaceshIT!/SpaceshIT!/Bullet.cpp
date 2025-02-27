/*
Team member: Lim Kai Xian
Group: CookieZ
studentID: S10195450H
*/

#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	this->movementSpeed = 7.f;
}

Bullet::Bullet(float pos_x, float pos_y, float dir_X, float dir_Y, float speed)
{
	this->texture.loadFromFile("Assets/Textures/rsz_bullet.png");
	this->shape.setTexture(this->texture);
	this->shape.setPosition(pos_x, pos_y);
	// this->shape.setOrigin(this->shape.getLocalBounds().width / 2.f, this->shape.getLocalBounds().height/ 2.f);
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