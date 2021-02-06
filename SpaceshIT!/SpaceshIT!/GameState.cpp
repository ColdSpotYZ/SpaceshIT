#include "stdafx.h"
#include "GameState.h"

void GameState::initVariables()
{
	this->playerVec = new Vector<Player*>;
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keys.ini");
	if (ifs.is_open())
	{
		std::string key;
		string key_code_map;

		while (ifs >> key >> key_code_map)
			this->keybinds[key] = this->supportedKeys->at(key_code_map);
	}
}

void GameState::initBackground()
{
	this->background.setSize(sf::Vector2f((float)this->window->getSize().x, (float)this->window->getSize().y));
	if (!this->backgroundTexture.loadFromFile("Assets/Background/game.png"))
		throw("ERROR::MAINMENUSTATE::INITBACKGROUND::Failed to load background image");
	this->background.setTexture(&this->backgroundTexture);
}

void GameState::initMusic()
{
	if (!this->music.openFromFile("Assets/Audio/theme.wav"))
		throw("ERROR::GAMESTATE::INITMUSIC::Unable to load music");
	else
	{
		this->music.setLoop(true);
		this->music.setVolume(15);
		this->music.play();
	}
}

void GameState::initFont()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
		throw("ERROR::MAINMENUSTATE::INITFONT::Failed to load menu font.");
}

void GameState::initPlayer()
{
	this->player1 = new Player((char*)"player1",
		sf::Vector2f( (float)(rand() % (this->window->getSize().x / 4 + 1)), (float)(rand() % (this->window->getSize().y + 1)))
		);
	this->player2 = new Player((char*)"player2",
		sf::Vector2f((float)(rand() % (this->window->getSize().x / 2 + 1)) + 3 * this->window->getSize().x / 4, (float)(rand() % (this->window->getSize().y + 1)))
		);
	this->playerVec->push_back(this->player1);
	this->playerVec->push_back(this->player2);
}

void GameState::initAsteroid()
{
	this->spawnTimerAsteroids = this->spawnTimerAsteroidsMax;
}

void GameState::initPacks()
{
	this->spawnTimerHealthPack = rand() % 101;
	this->SpawnTimerBulletPack = rand() % 101;
}

void GameState::initGUI()
{
	// Game over text
	this->playerWin.setFont(this->font);
	this->playerWin.setCharacterSize(50);
	this->playerWin.setFillColor(sf::Color::White);
}

void GameState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);
	this->pauseMenu->addButton("EXIT_STATE", 700.f , "QUIT");
}

void GameState::initPlayerGUI()
{
	for (unsigned i = 0; i < this->playerVec->getsize(); i++)
	{
		PlayerGUI* temp = new PlayerGUI(this->window, this->playerVec->at(i));
		this->playerGUIs.push_back(temp);
	}
}

GameState::GameState(sf::RenderWindow* window, std::map<string, int>* supportedKeys, Stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initVariables();
	initKeybinds();
	initBackground();
	initFont();
	initPauseMenu();
	initPlayer();
	this->initPlayerGUI();
	initGUI();
	initMusic();
	initAsteroid();
}

GameState::~GameState()
{
	this->playerVec->~Vector();
	delete this->pauseMenu;
	for (unsigned i = 0; i < this->playerGUIs.getsize(); i++)
	{
		delete this->playerGUIs.at(i);
	}
	for (auto* i : this->Asteroid_s)
	{
		delete i;
	}

}

void GameState::endState()
{
	// End game state
	this->quit = true;
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->paused)
		{
			this->pauseState();
			this->music.pause();
		}
		else
		{
			this->unpauseState();
			this->music.play();
		}
	}

	for (unsigned i = 0; i < this->playerVec->getsize(); i++)
	{
		playerVec->at(i)->updateBullets();
		playerVec->at(i)->Combat(player1, player2);
		playerVec->at(i)->Combat(player2, player1);

	}
}

void GameState::updatePlayerInput(const float& dt)
{
	for (unsigned i = 0; i < this->playerVec->getsize(); i++)
	{
		this->playerVec->at(i)->update(dt, this->keybinds);
	}
}

void GameState::updatePlayerGUI(const float& dt)
{
	for (unsigned i = 0; i < this->playerGUIs.getsize(); i++)
		this->playerGUIs.at(i)->update(dt);
}

void GameState::updateAsteroid()
{
	this->spawnTimerAsteroids += 0.2f;
	if (this->spawnTimerAsteroids >= this->spawnTimerAsteroidsMax)
	{
		Asteroids* ATemp = new Asteroids(rand() % this->window->getSize().x - 20.f, -100.f);
		this->Asteroid_s.push_back(ATemp);
		this->spawnTimerAsteroids = 0.f;
	}

	this->AsteroidsDamage(player1);
	this->AsteroidsDamage(player2);

	for (int i = 0; i < this->Asteroid_s.getsize(); i++)
	{
		Asteroid_s[i]->update();

		// Culling of Asteroid at the bottom of the screen
		if (this->Asteroid_s[i]->getBounds().top > this->window->getSize().y)
		{
			this->Asteroid_s.erase(i);
			// std::cout << this->Asteroid_s.getsize() << endl;
		}
	}
}
void GameState::updatePacks()
{
	// Updates Health Packs
	this->spawnTimerHealthPack += 0.2f;
	if (this->spawnTimerHealthPack >= this->spawnTimerHealthPackMax)
	{
		HealthPack* HPTemp = new HealthPack(rand() % this->window->getSize().x - 20.f, rand() % this->window->getSize().y - 20.f);
		this->HealthPacks.push_back(HPTemp);
		this->spawnTimerHealthPack = 0.f;
	}

	// Updates Bullet Packs
	this->SpawnTimerBulletPack += 0.2f;
	if (this->SpawnTimerBulletPack >= this->spawnTimerBulletPackMax)
	{
		BulletPack* BPTemp = new BulletPack(rand() % this->window->getSize().x - 20.f, rand() % this->window->getSize().y - 20.f);
		this->BulletPacks.push_back(BPTemp);
		this->SpawnTimerBulletPack = 0.f;
	}
}




void GameState::updateCollision()
{
	for (int i = 0; i < this->playerVec->getsize(); i++)
	{
		if (this->playerVec->at(i)->getBounds().left < 0.f)
		{
			this->playerVec->at(i)->setPos(0.f + this->playerVec->at(i)->getBounds().width / 2.f, this->playerVec->at(i)->getBounds().top + this->playerVec->at(i)->getBounds().height / 2.f);
		}
		else if (this->playerVec->at(i)->getBounds().left + this->playerVec->at(i)->getBounds().width > this->window->getSize().x)
		{
			this->playerVec->at(i)->setPos(this->window->getSize().x - this->playerVec->at(i)->getBounds().width / 2.f, this->playerVec->at(i)->getBounds().top + this->playerVec->at(i)->getBounds().height / 2.f);
		}
		if (this->playerVec->at(i)->getBounds().top < 0.f)
		{
			this->playerVec->at(i)->setPos(this->playerVec->at(i)->getBounds().left + this->playerVec->at(i)->getBounds().width / 2.f, 0.f + this->playerVec->at(i)->getBounds().height / 2.f);
		}
		else if (this->playerVec->at(i)->getBounds().top + this->playerVec->at(i)->getBounds().height >= this->window->getSize().y)
		{
			this->playerVec->at(i)->setPos(this->playerVec->at(i)->getBounds().left + this->playerVec->at(i)->getBounds().width / 2.f, this->window->getSize().y - this->playerVec->at(i)->getBounds().height / 2.f);
		}
	}
}

void GameState::AsteroidsDamage(Player* player)
{
	for (unsigned i = 0; i < this->Asteroid_s.getsize(); i++)
	{
		if (this->Asteroid_s[i]->getBounds().intersects(player->getBounds()))
		{
			Asteroid_s.erase(i);
			player->takeDamage();
		}
	}
}

void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("EXIT_STATE"))
		this->endState();
}

void GameState::updateGameStateEnd()
{
	for (unsigned i = 0; i < this->playerVec->getsize(); i++)
	{
		if (this->playerVec->at(i)->getHp() <= 0)
		{
			this->endGame = true;
			if (this->playerVec->at(i)->getPlayerNum() == 1)
				this->playerWin.setString("Player 2 wins \n Press ESC to exit");
			else
				this->playerWin.setString("Player 1 wins \n Press ESC to exit");
		}
	}
}

void GameState::update(const float& dt)
{
	// GameState updates
	this->updateMousePosition();
	this->updateKeyTime(dt);
	

	if (!this->endGame)
	{
		this->updateInput(dt);
		if (!this->paused)
		{
			this->updateCollision();
			this->updatePlayerInput(dt);
			this->updatePlayerGUI(dt);
			this->updateAsteroid();
			updateGameStateEnd();
		}
		else
		{
			this->pauseMenu->update(this->mousePosView);
			this->updatePauseMenuButtons();
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
		{
			this->endState();
		}
	}
}

void GameState::render(sf::RenderTarget* target)
{
	target->draw(this->background);
	if (this->endGame)
		target->draw(this->playerWin);
	else
	{
		for (unsigned i = 0; i < this->playerVec->getsize(); i++)
			playerVec->at(i)->render(target);
		for (unsigned i = 0; i < this->playerGUIs.getsize(); i++)
			this->playerGUIs.at(i)->render(target);

		for (auto* Asteroid : this->Asteroid_s)
		{
			Asteroid->render(this->window);
		}

	if (this->paused)
	{
		this->pauseMenu->render(target);
	}
}
