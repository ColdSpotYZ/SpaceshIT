/*
Team member: Lim Kai Xian
Group: CookieZ
studentID: S10195450H
*/

#pragma once
class HealthPack
{
	private:
		sf::Sprite Shape;
		sf::Texture texture;

		void initShape();

	public:
		HealthPack();

		HealthPack(float pos_x, float pos_y);

		~HealthPack();

		// Functions
		void render(sf::RenderTarget* target);

		// Accessors
		const sf::FloatRect getBounds() const;

};

