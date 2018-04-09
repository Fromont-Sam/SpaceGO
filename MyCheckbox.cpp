#include "MyCheckbox.h"
#include <iostream>

/*
* Constructor
*/
MyCheckbox::MyCheckbox()
{
	if (!texture.loadFromFile("images/settings/checkbox.png")) {};
	if (!checkTexture.loadFromFile("images/settings/checkbox_s.png")) {};
	sprite = sf::Sprite(texture);
}

/*
* Destructor
*/
MyCheckbox::~MyCheckbox()
{
}

//Setters and getters
void MyCheckbox::setPosition(int x, int y)
{
	sprite.setPosition(x, y);
}

bool MyCheckbox::setChecked(int x, int y)
{
	if (sprite.getGlobalBounds().contains(x, y)) {
		return true;
	}
	return false;
}

void MyCheckbox::setChecked(bool checked) {
	if (checked) {
		sprite.setTexture(checkTexture);
	}
	else {
		sprite.setTexture(texture);
	}
	_checked = checked;
}

sf::Sprite MyCheckbox::getSprite() const
{
	return sf::Sprite(sprite);
}


bool MyCheckbox::isChecked() const
{
	return _checked;
}

int MyCheckbox::getX() const
{
	return sprite.getPosition().x;
}

int MyCheckbox::getY() const
{
	return sprite.getPosition().y;
}
