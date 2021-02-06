#include "stdafx.h"
#include "BulletPack.h"

void BulletPack::initShape()
{
	this->texture.loadFromFile("Assets/Textures/rsz_1bulletpack.png");
	this->Shape.setTexture(this->texture);
}

BulletPack::BulletPack()
{
	this->initShape();
}

BulletPack::BulletPack(float pos_x, float pos_y)
{
	this->initShape();
	this->Shape.setPosition(pos_x, pos_y);
}

BulletPack::~BulletPack()
{
	// Empty
}

void BulletPack::render(sf::RenderTarget* target)
{
	target->draw(this->Shape);
}

const sf::FloatRect BulletPack::getBounds() const
{
	return this->Shape.getGlobalBounds();
}
