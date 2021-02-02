#include "Bullet.h"

void Bullet::InitVairables()
{
	this->speed = this->speed;
	this->state = this->state;
}

Bullet::Bullet() 
{
	this->initVariables();
};

Bullet::~Bullet()
{

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
	this->sprite->move(this->speed * x * dt, this->speed * y * dt);
}

