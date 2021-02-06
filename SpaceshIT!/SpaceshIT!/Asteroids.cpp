#include "stdafx.h"
#include "Asteroids.h"

void Asteroids::initShape()
{
	this->texture.loadFromFile("Assets/Textures/rsz_1asteroids_a.png");
	this->Shape.setTexture(this->texture);
	this->Shape.rotate(rand() % 360 + 1);
}

void Asteroids::initVariables()
{
	this->hpMax = (rand() % 2 + 1) * 25;
	this->hp = hpMax;
	this->direction = (rand() % 7) - 3;
}

Asteroids::Asteroids()
{
	this->initVariables();
}

Asteroids::Asteroids(float pos_x, float pos_y)
{
	this->initShape();
	this->initVariables();
	this->Shape.setPosition(pos_x, pos_y);
}

Asteroids::~Asteroids()
{
	// Empty
}

void Asteroids::update()
{
	this->Shape.move(direction, 2.f);
}

void Asteroids::render(sf::RenderTarget* target)
{
	target->draw(this->Shape);
}

const sf::FloatRect Asteroids::getBounds() const
{
	return this->Shape.getGlobalBounds();
}
