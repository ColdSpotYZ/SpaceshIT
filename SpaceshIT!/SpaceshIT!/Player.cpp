#include "Player.h"

void Player::initVariables()
{
	this->health = this->max_health;
	this->ammo = this->max_ammo;
	this->speed = this->max_speed;
}

void Player::initGUI()
{
	this->playerHpBar.setSize(sf::Vector2f(this->getBounds().width, 10.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(this->getPos().x, this->getPos().y - (this->getBounds().height / 4)));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(30, 30, 30, 240));
}

Player::Player()
{
	this->initVariables();
	this->initGUI();
}

Player::Player(char* filename) : Actor(filename)
{
	this->initVariables();
	this->initSprite(sf::Vector2f(0.4f, 0.4f));
	this->initGUI();
}

Player::~Player()
{

}

const int Player::getHp() const
{
	return this->health;
}

const int Player::getHpMax() const
{
	return this->max_health;
}

void Player::move(const float dt, const float x, const float y)
{
	this->sprite.move(this->speed * x * dt, this->speed * y * dt);
}

void Player::takeDamage()
{
	this->health -= 20;
	if (this->health < 0)
		this->health = 0;
}

void Player::shoot()
{
	this->ammo--;
	if (this->ammo < 0)
		this->ammo = 0;
}

void Player::updateGUI()
{
	this->playerHpBar.setSize(sf::Vector2f(this->getBounds().width * (static_cast<float>(this->getHp()) / this->getHpMax()), this->playerHpBar.getSize().y));
	this->playerHpBar.setPosition(sf::Vector2f(this->getPos().x, this->getPos().y - (this->getBounds().height / 4)));
	this->playerHpBarBack.setPosition(sf::Vector2f(this->getPos().x, this->getPos().y - (this->getBounds().height / 4)));
}

void Player::update(const float dt)
{
}

void Player::update(const float dt, bool wasd = true)
{
	if (wasd)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			this->move(dt, -1.f, 0.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			this->move(dt, 1.f, 0.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			this->move(dt, 0.f, -1.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			this->move(dt, 0.f, 1.f);
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			this->move(dt, -1.f, 0.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			this->move(dt, 1.f, 0.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			this->move(dt, 0.f, -1.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			this->move(dt, 0.f, 1.f);
	}
	this->updateGUI();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	target->draw(this->playerHpBarBack);
	target->draw(this->playerHpBar);
}


