#include "Laser.h"
#include <iostream>

/*
* Default constructor
*/
Laser::Laser(int x, int y) : Laser(x, y, Laser::LASER_TYPE_BLUE)
{
}

/*
* Constructor
*/
Laser::Laser(int x, int y, int type)
{
	std::string path;
	switch (type) {
	case Laser::LASER_TYPE_GREEN:
		path = "images/lasers/green.png"; 
		_type = Laser::LASER_TYPE_GREEN; break;
	case Laser::LASER_TYPE_RED:
		path = "images/lasers/red.png";
		_type = Laser::LASER_TYPE_RED;  break;
	case Laser::LASER_TYPE_YELLOW:
		path = "images/lasers/yellow.png";
		_type = Laser::LASER_TYPE_YELLOW;  break;
	default:
		path = "images/lasers/blue.png";
		_type = Laser::LASER_TYPE_BLUE;  break;
	}
	if (!texture.loadFromFile(path)) {};
	sprite = sf::Sprite(texture);
	sprite.setPosition(x, y);
}

/*
* Destructor
*/
Laser::~Laser()
{
}

/*
* Move the laser with a constant speed 
*/
void Laser::move()
{
	sprite.move(20, 0);
}

/*
* Set the laser sprite
*/
void Laser::setSprite() {
	sprite.setTexture(texture);
}

/*
* Get the laser type
*/
int Laser::getType() const
{
	return _type;
}

/*
* Get the laser sprite
*/
sf::Sprite Laser::getSprite() const
{
	return sf::Sprite(sprite);
}
