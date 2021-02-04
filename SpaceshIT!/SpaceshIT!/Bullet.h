#pragma once
#include "Actor.h"


class Bullet : public Actor
{
	

	private:
		sf::Sprite shape;
		sf::Texture* texture;

		sf::Vector2f direction;
		float movementSpeed;

		bool state;

		
		void InitVairables();

	public:
		Bullet();

		Bullet(sf::Texture& texture, float dir_X, float dir_Y, float speed);

		~Bullet();

		void update();

		void render(sf::RenderTarget* target);

		bool getState();

		void changeState(bool state);

		void move(const float dt, const float x, const float y);
};

