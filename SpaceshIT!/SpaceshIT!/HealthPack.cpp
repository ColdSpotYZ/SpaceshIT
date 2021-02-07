/*
Team member: Lim Kai Xian
Group: CookieZ
studentID: S10195450H
*/

#include "stdafx.h"
#include "HealthPack.h"

void HealthPack::initShape()
{
	this->texture.loadFromFile("Assets/Textures/Healthpack.v3.png");
	this->Shape.setTexture(this->texture);
}

HealthPack::HealthPack()
{
	this->initShape();
}

HealthPack::HealthPack(float pos_x, float pos_y)
{
	this->initShape();
	this->Shape.setPosition(pos_x, pos_y);
}

HealthPack::~HealthPack()
{
	// Empty
}

void HealthPack::render(sf::RenderTarget* target)
{
	target->draw(this->Shape);
}

const sf::FloatRect HealthPack::getBounds() const
{
	return this->Shape.getGlobalBounds();
}
