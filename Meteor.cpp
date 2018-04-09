#include "Meteor.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>   

/*
* Constructor
*/
Meteor::Meteor(int minX, int minY, int y)
{
	//Skin random generator
	int skinType = y % 3;
	_health = 2;
	//Sprite loading
	std::stringstream ss;
	ss << "images/obstacles/meteor" << skinType << ".png";
	if (!texture.loadFromFile(ss.str())) {};
	sprite = sf::Sprite(texture);
	//Set position out of screen
	int posX = minX + texture.getSize().x;
	int posY = y % (minY-texture.getSize().y);
	sprite.setPosition(posX, posY);
	//Set type
	_type = Obstacle::TYPE_METEOR;
}

/*
* Destructor
*/
Meteor::~Meteor()
{
}

/*
* Remove health when the meteor is hit
*/
bool Meteor::takeDamage()
{
	_health -= 1;
	if (_health <= 0) {
		return false;
	}
	return true;
}
