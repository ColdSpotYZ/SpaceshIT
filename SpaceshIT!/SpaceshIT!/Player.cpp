#include "stdafx.h"
#include "Player.h"


void Player::initVariables()
{
	this->health = this->max_health;
	this->speed = this->max_speed;
	this->attackCoolDownMax = 10.f;
	this->attackCoolDown = this->attackCoolDownMax;
	this->ammo = this->max_ammo;
}

Player::Player()
{
	this->initVariables();
}

Player::Player(char* filename, sf::Vector2f pos) : Actor(filename, pos)
{
	if (filename == "player1")
		this->playerNum = 1;
	else
		this->playerNum = 2;
	this->initVariables();
	this->initSprite(pos, sf::Vector2f(0.4f, 0.4f));
	if (this->playerNum == 1)
		this->sprite->setRotation(90);
	else
		this->sprite->setRotation(270);
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

const int Player::getPlayerNum() const
{
	return this->playerNum;
}

void Player::move(const float dt, const float x, const float y)
{
	this->sprite->move(this->speed * x * dt, this->speed * y * dt);
}

void Player::takeDamage()
{
	this->health -= 20;
	if (this->health < 0)
	{
		this->health = 0;
	}
}

void Player::shoot()
{
	this->ammo -= 1;
	if (this->ammo < 0)
	{
		this->ammo = 0;
	}
}

void Player::heal()
{
	this->health += 60;
	if (this->health > this->max_health)
	{
		this->health = this->max_health;
	}
}

void Player::restockammo()
{
	this->ammo += 20;
	if (this->ammo > this->max_ammo)
	{
		this->ammo = this->max_ammo;
	}
}

void Player::updateBullets()
{
	for (unsigned counter = 0; counter < this->bullets.getsize(); counter++)
	{
		bullets.at(counter)->update();

		// Bulleting culling
		if (bullets.at(counter)->getBounds().top + bullets.at(counter)->getBounds().height < 0.f || 
			bullets.at(counter)->getBounds().top + bullets.at(counter)->getBounds().height > 900.f ||
			bullets.at(counter)->getBounds().width + bullets.at(counter)->getBounds().left > 1600.f ||
			bullets.at(counter)->getBounds().width + bullets.at(counter)->getBounds().left < 0.f)
		{
			//Delete bullet
			// std::cout << "culling of bullets" << endl;
			delete this->bullets.at(counter);
			this->bullets.erase(counter);
		}

	}
}

const bool Player::canAttack()
{
	if (this->attackCoolDown >= this->attackCoolDownMax)
	{
		this->attackCoolDown = 0.f;
		return true;
	}
	return false;
}

void Player::Combat(Player* player, Player* player2)
{
	for (unsigned i = 0; i < player->bullets.getsize(); i++)
	{
		if (player->bullets[i]->getBounds().intersects(player2->getBounds()))
		{
			player->bullets.erase(i);
			player2->takeDamage();
		}
	}
}

void Player::updateAttack()
{
	if (this->attackCoolDown < this->attackCoolDownMax)
		this->attackCoolDown += 0.5f;
}

void Player::update(const float dt)
{
}


void Player::update(const float dt, Map<std::string, int> keybinds)
{
	this->queuePlayerLocation();
	bool isPress = false;
	if (this->playerNum == 1)
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
		/*
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("p1_back")))
		{
			this->p1Velocity.y = 1;
			this->p1Velocity.x = -1;
		}
		*/
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("p1_shoot")) && canAttack() && ammo > 0)
		{
			Bullet* tempBullet = new Bullet(this->getPos().x - 5.f + (5.f * sin(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0))),
				this->getPos().y - this->sprite->getLocalBounds().height / 50.f + (-0.f * sin(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0))),
				1 * sin(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0)),
				(-1 * cos(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0))), 7.f);
			this->bullets.push_back(tempBullet);
			this->shoot();
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

		/*
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("p2_back")))
		{
			this->p2Velocity.y = 1;
			this->p2Velocity.x = -1;
		}
		*/
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("p2_shoot")) && canAttack() && ammo > 0)
		{
			Bullet* tempBullet = new Bullet(this->getPos().x - 5.f + (5.f * sin(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0))),
				this->getPos().y - this->sprite->getLocalBounds().height / 50.f + (-0.f * sin(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0))),
				1 * sin(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0)),
				(-1 * cos(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0))), 7.f);
			this->bullets.push_back(tempBullet);
			this->shoot();
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
	this->updateAttack();
}

void Player::queuePlayerLocation()
{
	sf::Vector2f CurrentLocation = this->sprite->getPosition();
	sf::Vector2f location;
	std::string hash;
	if (!this->PlayerLocations.isEmpty())
		this->PlayerLocations.getBack(location, hash);
	this->PlayerLocations.enqueue_back(CurrentLocation);
	xhash("test");
	if (!this->PlayerLocations.isEmpty())
	{
		if ("" == hash)
		{
			if (!((CurrentLocation.x - location.x) < 8) && ((CurrentLocation.x - location.x) > -8) && ((CurrentLocation.y - location.y) < 8) && ((CurrentLocation.y - location.y) > -8))
			{
				std::cout << "invalid movement" << endl;
			}
		}
	}

	
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(*this->sprite);

	for (auto* i : this->bullets)
	{
		i->render(target);
	}
}


