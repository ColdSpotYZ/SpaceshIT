#include "Bullet.h"

void Bullet::InitVairables()
{
	speed = this->speed;
	state = this->state;
}

Bullet::Bullet() {
	initVariables();
	x_axis = 0;
	y_axis = 0;
};

Bullet::Bullet(int x, int y) {
	initVariables();
	x_axis = x;
	y_axis = y;
};

