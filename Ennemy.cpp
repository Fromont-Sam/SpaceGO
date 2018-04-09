#include "Ennemy.h"
#include <sstream>
#include <iostream>

/*
* Constructor
*/
Ennemy::Ennemy(int minX, int minY, int y)
{
	//Init variables
	_health = 2;
	_direction = y % 2;
	int skinType = y % 5;
	//Sprite loading
	std::stringstream ss;
	ss << "images/obstacles/ennemy" << skinType << ".png";
	if (!texture.loadFromFile(ss.str())) {};
	sprite = sf::Sprite(texture);
	//Set position out of screen
	int posX = minX + texture.getSize().x;
	int posY = y % (minY - texture.getSize().y); // random % (window size - ennemy size) avoid out of window spawn
	sprite.setPosition(posX, posY);
	//Set type
	_type = Obstacle::TYPE_ENNEMY;
}

/*
* Destructor
*/
Ennemy::~Ennemy()
{
}

/*
* Move the ennemy with a speed and with a direction
*/
void Ennemy::move(float speed)
{
	sprite.move(-speed, 0);
	if (_direction && (sprite.getPosition().y - speed/2) > 0) {
		sprite.move(0, -5);
	}
	else {
		_direction = false;
	}
	if (!_direction && (sprite.getPosition().y + texture.getSize().y + speed/2) < 810) {
		sprite.move(0, +5);
	}
	else {
		_direction = true;
	}
}

/*
* Remove health when a ennemy is hit
*/
bool Ennemy::takeDamage()
{
	_health -= 1;
	if (_health <= 0) {
		return false;
	}
	return true;
}
