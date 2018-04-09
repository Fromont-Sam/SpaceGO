#include "MyProgressBar.h"

/*
* Constructor
*/
MyProgressBar::MyProgressBar(std::string path)
{
	if (!texture.loadFromFile(path)) {};
	sprite = sf::Sprite(texture);
	if (!rectTexture.loadFromFile("images/settings/rect_bar.png")) {};
	rectSprite = sf::Sprite(rectTexture);
	_percentage = 50;
	_start = 0;
	_end = 100;
}

/*
* Advanced constructor
*/
MyProgressBar::MyProgressBar(int start, int end, std::string path) : MyProgressBar(path)
{
	_start = start;
	_end = end;
}

/*
* Destructor
*/
MyProgressBar::~MyProgressBar()
{
}

//Setters and getters
void MyProgressBar::setPosition(int x, int y)
{
	rectSprite.setPosition(x, y);
}

void MyProgressBar::setPositionBar(int x, int y)
{
	sprite.setPosition(x, y);
}

/*
* Return a percentage calculated with the coordinates
*/
bool MyProgressBar::setPercentage(int x, int y)
{
	if (sprite.getGlobalBounds().contains(x, y)) {
		rectSprite.setPosition(x, rectSprite.getPosition().y);
		_percentage = ((float) x - sprite.getPosition().x) / texture.getSize().x;
		return true;
	}
	return false;
}

/*
* Set the percentage
*/
bool MyProgressBar::setPercentage(int percentage) {
	if (percentage>=0 && percentage<=100) {
		_percentage = percentage / 100.;
		rectSprite.setPosition((sprite.getPosition().x + texture.getSize().x*_percentage), rectSprite.getPosition().y);
		return true;
	}
	return false;
}

sf::Sprite MyProgressBar::getSprite() const
{
	return sf::Sprite(rectSprite);
}

sf::Sprite MyProgressBar::getSpriteBar() const
{
	return sf::Sprite(sprite);
}

int MyProgressBar::getPercentage() const
{
	return _start + ((_end - _start)*_percentage);
}

int MyProgressBar::getX() const
{
	return sprite.getPosition().x;
}

int MyProgressBar::getY() const
{
	return sprite.getPosition().y;
}
