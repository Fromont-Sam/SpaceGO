#include "Star.h"

/*
* Constructor
*/
Star::Star(int minX, int minY, int y)
{
	//Sprite loading
	if (!texture.loadFromFile("images/obstacles/star.png")) {};
	sprite = sf::Sprite(texture);
	//Set position out of screen
	int posX = minX + texture.getSize().x;
	int posY = y % (minY - texture.getSize().y);
	sprite.setPosition(posX, posY);
	//Set type
	_type = Obstacle::TYPE_STAR;
}

/*
* Destructor
*/
Star::~Star()
{
}
