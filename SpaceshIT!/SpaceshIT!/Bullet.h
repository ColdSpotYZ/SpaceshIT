#pragma once
#include "Actor.h"


class Bullet
{
	private:
		sf::Sprite shape;
		sf::Texture texture;
		sf::Vector2f direction;
		float movementSpeed;
		 
	public:
		Bullet();

		Bullet(float pos_x, float pos_y, float dir_X, float dir_Y, float speed);

		~Bullet();

		 // Accessor
		const sf::FloatRect getBounds() const;

		void update();

		void render(sf::RenderTarget* target);
};

