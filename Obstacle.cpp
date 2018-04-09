#include "Obstacle.h"

/*
* Constructor
*/
Obstacle::Obstacle()
{
}

/*
* Destructor
*/
Obstacle::~Obstacle()
{
}

/*
* Move the obstacle with a speed
*/
void Obstacle::move(float speed)
{
	sprite.move(-speed, 0);
}

/*
* Get the obstacle type
*/
int Obstacle::getType() const
{
	return _type;
}

/*
* Set the obstacle sprite
*/
void Obstacle::setSprite() {
	sprite.setTexture(texture);
}

/*
* Get the obstacle sprite
*/
sf::Sprite Obstacle::getSprite() const
{
	return sf::Sprite(sprite);
}

