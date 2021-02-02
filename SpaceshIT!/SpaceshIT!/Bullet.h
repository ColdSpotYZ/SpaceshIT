#pragma once
#include "Actor.h"


class Bullet : public Actor
{
	private:
		float speed;
		bool state;

		
		void InitVairables();

	public:
		Bullet();

		~Bullet();

		bool getState();

		bool changeState(bool state);

		void move(const float dt, const float x, const float y);
};

