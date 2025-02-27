/*
Team member: Jason Chua
Group: CookieZ
studentID: S10195450H
*/
#pragma once

class Actor
{
protected:
	sf::Sprite* sprite;
	sf::Texture* texture;
	float movementSpeed;

	// Functions
	void initTexture(char*);
	void initSprite(sf::Vector2f pos, sf::Vector2f);
	void initVariables();
public:
	Actor();
	Actor(char*, sf::Vector2f pos);
	virtual ~Actor();

	// Component
	void createSprite(sf::Texture* texture);

	// Accessors
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	sf::Sprite* getSprite();
	sf::Texture* getTexture();

	// Setters
	void setPos(const sf::Vector2f);
	void setPos(const float x, const float y);
	void setSprite(sf::Sprite*);
	void setTexture(sf::Texture*);

	// Functions
	void move(const float dt, const float x, const float y, float speed);
	virtual void update(const float dt) = 0;
	virtual void render(sf::RenderTarget* target);
};

