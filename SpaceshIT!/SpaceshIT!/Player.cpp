#include "stdafx.h"
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
	/*this->initGUI();*/
}

Player::~Player()
{
	// Delete Textures

	for (auto* i : this->bullets)
	{
		delete i;
	}
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
	this->sprite->move(this->speed * x * dt, this->speed * y * dt);
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

void Player::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		// Bulleting culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(&bullet);
			--counter;
		}
		++counter;
	}
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

void Player::update(const float dt, std::map<std::string, int> keybinds, bool wasd = true)
{
	bool isPress = false;
	if (wasd)
	{
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("p1_left")))
		{
			isPress = true;
			this->rotateAmount1 = -0.03f;
		}
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("p1_right")))
		{
			isPress = true;
			this->rotateAmount1 = 0.03f;
		}
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("p1_front")))
		{
			this->p1Velocity.y = -1;
		
			this->p1Velocity.x = 1;
		}
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("p1_back")))
		{
			this->p1Velocity.y = 1;
			this->p1Velocity.x = -1;
		}
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("p1_shoot")))
		{
			Bullet* tempBullet = new Bullet(this->getPos().x - (this->sprite->getLocalBounds().width / 8) , this->getPos().y - (this->sprite->getLocalBounds().height / 8), 0.f, -1.f, 5.f);
			this->bullets.push_back(tempBullet);
			std::cout << "P1_shooting" << endl;
		}

		if (!isPress)
			this->rotation1 = 0;
		if (this->rotation1 < 0 && this->rotateAmount1 > 0)
			this->rotation1 = 0;
		else if (this->rotation1 > 0 && this->rotateAmount1 < 0)
			this->rotation1 = 0;
		this->rotation1 += this->rotateAmount1;
		this->sprite->rotate(this->rotation1);
		this->move(dt, this->p1Velocity.x * sin(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0)), this->p1Velocity.y * cos(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0)));
		this->p1Velocity.x = 0;
		this->p1Velocity.y = 0;
		this->rotateAmount1 = 0;
	}
	else
	{
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("p2_left")))
		{
			isPress = true;
			this->rotateAmount2 = -0.02f;
		}
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("p2_right")))
		{
			isPress = true;
			this->rotateAmount2 = 0.02f;
		}
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("p2_front")))
		{
			this->p2Velocity.y = -1;
			this->p2Velocity.x = 1;
		}
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("p2_back")))
		{
			this->p2Velocity.y = 1;
			this->p2Velocity.x = -1;
		}
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("p2_shoot")))
		{
			Bullet* tempBullet = new Bullet(this->getPos().x, this->getPos().y, 0.f, 0.f, 0.f);
			this->bullets.push_back(tempBullet);
			std::cout << "P2_shooting" << endl;
		}

		if (!isPress)
			this->rotation2 = 0;
		if (this->rotation2 < 0 && this->rotateAmount2 > 0)
			this->rotation2 = 0;
		else if (this->rotation2 > 0 && this->rotateAmount2 < 0)
			this->rotation2 = 0;
		this->rotation2 += this->rotateAmount2;
		this->sprite->rotate(this->rotation2);
		this->move(dt, this->p2Velocity.x * sin(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0)), this->p2Velocity.y * cos(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0)));
		this->p2Velocity.x = 0;
		this->p2Velocity.y = 0;
		this->rotateAmount2 = 0;
	}
	/*this->updateGUI();*/
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(*this->sprite);

	for (auto* i : this->bullets)
	{
		i->render(target);
	}

	//target->draw(this->playerHpBarBack);
	//target->draw(this->playerHpBar);
}


