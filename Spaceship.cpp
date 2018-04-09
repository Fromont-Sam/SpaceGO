#include "Spaceship.h"
#include <sstream>
#include <iostream>

/*
* Get the string value of a color between 0 and 7
*/
std::string Spaceship::getColor(int color) const
{
	switch (color)
	{
	case Spaceship::SPACESHIP_COLOR_RED: return "red";
	case Spaceship::SPACESHIP_COLOR_YELLOW: return "yellow";
	case Spaceship::SPACESHIP_COLOR_GREEN: return "green";
	case Spaceship::SPACESHIP_COLOR_BLUE: return "blue";
	case Spaceship::SPACESHIP_COLOR_PURPLE: return "purple";
	case Spaceship::SPACESHIP_COLOR_PINK: return "pink";
	case Spaceship::SPACESHIP_COLOR_GREY: return "grey";
	case Spaceship::SPACESHIP_COLOR_ORANGE: return "orange";
	default:
		return "red";
	}
}

/*
* Initialise spaceship speed, health and guns position
*/
void Spaceship::initSpaceship(int type)
{
	switch (type)
	{
	case Spaceship::SPACESHIP_SKIN_0: _speed = 9; _health = _maxHealth = 120;
		guns = sf::Vector3i(68,44,0);
		break;
	case Spaceship::SPACESHIP_SKIN_1: _speed = 6; _health = _maxHealth = 180;
		guns = sf::Vector3i(84, 30, 86); _doubleGun=true;
		break;
	case Spaceship::SPACESHIP_SKIN_2: _speed = 6; _health = _maxHealth = 180;
		guns = sf::Vector3i(54, 64, 0);
		break;
	case Spaceship::SPACESHIP_SKIN_3: _speed = 9; _health = _maxHealth = 120;
		guns = sf::Vector3i(95, 42, 0);
		break;
	case Spaceship::SPACESHIP_SKIN_4: _speed = 6; _health = _maxHealth = 180; 
		guns = sf::Vector3i(80, 42, 85); _doubleGun = true;  
		break;
	case Spaceship::SPACESHIP_SKIN_5: _speed = 9; _health = _maxHealth = 120; 
		guns = sf::Vector3i(46, 17, 74); _doubleGun = true;  
		break;
	case Spaceship::SPACESHIP_SKIN_6: _speed = 12; _health = _maxHealth = 90; 
		guns = sf::Vector3i(55, 15, 89); _doubleGun = true;  
		break;
	case Spaceship::SPACESHIP_SKIN_7: _speed = 12; _health = _maxHealth = 90;
		guns = sf::Vector3i(42, 21, 75); _doubleGun = true; 
		break;
	case Spaceship::SPACESHIP_SKIN_8: _speed = 12; _health = _maxHealth = 90; 
		guns = sf::Vector3i(37, 45, 0);
		break;
	}
}

/*
* Default constructor
*/
Spaceship::Spaceship()
{
}

/*
* Advanced Default Constructor
*/
Spaceship::Spaceship(int skinType) : Spaceship(skinType, Spaceship::SPACESHIP_COLOR_RED)
{
}

/*
* Constructor
*/
Spaceship::Spaceship(int skinType, int colorType) {
	std::stringstream path;
	_skin = skinType;
	_color = colorType;
	initSpaceship(skinType);
	path << "images/spaceships/spaceship" << skinType << "/" << getColor(colorType) << ".png";
	if (!texture.loadFromFile(path.str())) {};
	sprite = sf::Sprite(texture);
}

/*
* Destructor
*/
Spaceship::~Spaceship()
{
}

/*
* Set spaceship position
*/
void Spaceship::setPosition(int x, int y)
{
	sprite.setPosition(x, y);
}

/*
* Move the spaceship with it speed and to a direction
*/
void Spaceship::move(int keyX, int keyY)
{
	if(keyX>=-1 && keyX<= 1 && keyY>=-1 && keyY<=1)
	sprite.move(keyX*_speed, keyY*_speed);
}

/*
* Remove health when the spaceship is hit
*/
void Spaceship::takeDamages()
{
	_health -= 30;
	if (_health <= 0) {
		_health = 0;
	}
}

/*
* Set the spaceship skin
*/
void Spaceship::setSkin(int skinType, int colorType)
{
	std::stringstream path;
	_skin = skinType;
	_color = colorType;
	initSpaceship(skinType);
	path << "images/spaceships/spaceship" << skinType << "/" << getColor(colorType) << ".png";
	if (!texture.loadFromFile(path.str())) {};
	sprite = sf::Sprite(texture);
}

/*
* Add health to the spaceship
*/
void Spaceship::addHealth()
{
	_health += 30;
	if (_health > _maxHealth) {
		_health = _maxHealth;
	}
}

//Getters 
int Spaceship::getWidth()  const
{
	return texture.getSize().x;
}

int Spaceship::getHeight()  const
{
	return texture.getSize().y;
}

int Spaceship::getSkin()  const
{
	return _skin;
}

int Spaceship::getColor()  const
{
	return _color;
}

int Spaceship::getX()  const
{
	return sprite.getPosition().x;
}

int Spaceship::getY()  const
{
	return sprite.getPosition().y;
}

int Spaceship::getHealth() const
{
	return _health;
}

float Spaceship::getMaxHealth() const
{
	return _maxHealth;
}

bool Spaceship::hasDoubleGun() const
{
	return _doubleGun;
}

sf::Vector3i Spaceship::getGuns() const
{
	return sf::Vector3i(guns);
}

sf::Sprite Spaceship::getSprite()  const
{
	return sf::Sprite(sprite);
}
