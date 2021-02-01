#pragma once
#include "Actor.h"


class Bullet : public Actor
{
	private:
		int x_axis;
		int y_axis;
		float speed;
		bool state;

		
		void InitVairables();
	public:
		Bullet();
		Bullet(int x, int y);
		
};

