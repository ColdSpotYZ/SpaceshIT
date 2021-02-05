#include "stdafx.h"
#include "Player.h"


void Player::initVariables()
{
	this->health = this->max_health;
	this->speed = this->max_speed;
	this->attackCoolDownMax = 10.f;
	this->attackCoolDown = this->attackCoolDownMax;
}

Player::Player()
{
	this->initVariables();
}

Player::Player(char* filename) : Actor(filename)
{
	if (filename == "player1")
		this->playerNum = 1;
	else
		this->playerNum = 2;
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
		// std::cout << this->attackCoolDown << endl;
		return true;
	}
	return false;
	// std::cout << this->canAttack << endl;

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
	// std::cout << this->attackCoolDown << endl;
}

void Player::update(const float dt)
{
}

void Player::update(const float dt, std::map<std::string, int> keybinds)
{
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
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("p1_shoot")) && canAttack())
		{
			Bullet* tempBullet = new Bullet(this->getPos().x - 5.f + (5.f * sin(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0))),
				this->getPos().y - this->sprite->getLocalBounds().height / 50.f + (-0.f * sin(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0))),
				1 * sin(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0)),
				(-1 * cos(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0))), 7.f);
			this->bullets.push_back(tempBullet);
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
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keybinds.at("p2_shoot")) && canAttack())
		{
			Bullet* tempBullet = new Bullet(this->getPos().x - 5.f + (5.f * sin(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0))),
				this->getPos().y - this->sprite->getLocalBounds().height / 50.f + (-0.f * sin(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0))),
				1 * sin(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0)),
				(-1 * cos(this->sprite->getRotation() * ((2 * acos(0.0)) / 180.0))), 7.f);
			this->bullets.push_back(tempBullet);
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
	/*this->updateGUI();*/
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(*this->sprite);

	for (auto* i : this->bullets)
	{
		i->render(target);
	}
}


