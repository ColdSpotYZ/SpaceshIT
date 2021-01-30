#include "Player.h"

void Player::initTexture(char* filename)
{
	std::stringstream s;
	s << "Assets/Textures/" << filename << ".png";
	if (!this->texture.loadFromFile(s.str()))
	{
		std::cout << "ERROR::Player::INITTEXTURE::Could not load texture file." << std::endl;
	}
}

void Player::initSprite()
{
	// Set texture for sprite object
	this->sprite.setTexture(this->texture);

	// Resize sprite
	this->sprite.setScale(0.4f, 0.4f);
}

void Player::initVariables()
{
	this->health = 100;
	this->ammo = 20;
	this->speed = 10.f;
}

Player::Player()
{
	this->initVariables();
}

Player::Player(char* filename)
{
	this->initVariables();
	this->initTexture(filename);
	this->initSprite();
}

Player::~Player()
{

}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setPos(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPos(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::move(const float x, const float y)
{
	this->sprite.move(this->speed * x, this->speed * y);
}

void Player::takeDamage()
{
	this->health -= 20;
}

void Player::shoot()
{
	this->ammo--;
}

void Player::update(bool wasd = true)
{
	if (wasd)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			this->move(-1.f, 0.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			this->move(1.f, 0.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			this->move(0.f, -1.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			this->move(0.f, 1.f);
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			this->move(-1.f, 0.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			this->move(1.f, 0.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			this->move(0.f, -1.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			this->move(0.f, 1.f);
	}
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

