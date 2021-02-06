#pragma once


class Asteroids
{
	private:
		sf::Sprite Shape;
		sf::Texture texture;
		int hp;
		int hpMax;
		float direction;

		void initShape();
		void initVariables();

	public:
		Asteroids();

		Asteroids(float pos_x, float pos_y);

		~Asteroids();

		// Functions
		void update();

		void render(sf::RenderTarget* target);

		// Accessors
		const sf::FloatRect getBounds() const;
};

