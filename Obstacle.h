#include <SFML/Graphics.hpp>
#pragma once
class Obstacle
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	int _type, _health;
public:
	enum {
		TYPE_METEOR,
		TYPE_STAR,
		TYPE_BONUS,
		TYPE_ENNEMY
	};
	Obstacle();
	~Obstacle();
	virtual void move(float speed);
	virtual bool takeDamage() { return true; };
	virtual int getBonus() const { return -1; };
	//Getters
	int getType() const;
	//Setters
	void setSprite();
	sf::Sprite getSprite() const;
};

