#pragma once
class BulletPack
{
private:
	sf::Sprite Shape;
	sf::Texture texture;

	void initShape();

public:
	BulletPack();

	BulletPack(float pos_x, float pos_y);

	~BulletPack();

	// Functions
	void render(sf::RenderTarget* target);

	// Accessors
	const sf::FloatRect getBounds() const;
};

