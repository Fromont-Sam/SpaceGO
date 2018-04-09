#include "Bonus.h"
#include <iostream>
#include <sstream>

/*
* Constructor
*/
Bonus::Bonus(int minX, int minY, int y)
{
	_bonus = y % 5;
	//Sprite loading
	if (_bonus == Bonus::BONUS_TYPE_HEAL) {
		if (!texture.loadFromFile("images/obstacles/heal.png")) {};
	}
	else {
		if (!texture.loadFromFile("images/obstacles/random.png")) {};
	}
	sprite = sf::Sprite(texture);
	//Set position out of screen
	int posX = minX + texture.getSize().x;
	int posY = y % (minY - texture.getSize().y);
	sprite.setPosition(posX, posY);
	//Set type
	_type = Obstacle::TYPE_BONUS;
}

/*
* Destructor
*/
Bonus::~Bonus()
{
}

/*
* Return the bonus sprite for the bonus type parameter
*/
std::string Bonus::getBonusSprite(int typeBonus)
{
	if (typeBonus == -1) return "images/bonus/bonus.png";
	std::stringstream ss;
	ss << "images/bonus/bonus" << typeBonus << ".png";
	return ss.str();
}

/*
* Return the correct laser color for the bonus type parameter
*/
int Bonus::getColorLaser(int typeBonus)
{
	switch (typeBonus)
	{
	case Bonus::BONUS_TYPE_DAMAGE: return Laser::LASER_TYPE_RED;
	case Bonus::BONUS_TYPE_SPEED: return Laser::LASER_TYPE_GREEN;
	case Bonus::BONUS_TYPE_METEOR: return Laser::LASER_TYPE_YELLOW;
	default: return Laser::LASER_TYPE_BLUE; break;
	}
}

/*
* Return the bonus type as an integer
*/
int Bonus::getBonus() const
{
	return _bonus;
}
