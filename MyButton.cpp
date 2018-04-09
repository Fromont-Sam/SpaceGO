#include "MyButton.h"
#include <iostream>

/*
* Constructor
*/
MyButton::MyButton(std::string path)
{
	if (!buffer.loadFromFile("sounds/button.wav")) {}
	sound.setBuffer(buffer);
	sound.setVolume(70);
	texture = sf::Texture();
	if (!texture.loadFromFile(path)) {};
	sprite = sf::Sprite(texture);
}

/*
* Advanced Constructor
*/
MyButton::MyButton(std::string path, std::string pathSelected)
{
	if (!buffer.loadFromFile("sounds/button.wav")) {}
	sound.setBuffer(buffer);
	if (!texture.loadFromFile(path)) {};
	if (!selectedTexture.loadFromFile(pathSelected)) {};
	sprite = sf::Sprite(texture);
}

/*
* Destructor
*/
MyButton::~MyButton()
{
}

/*
* Change texture when button is selected for example
*/
void MyButton::changeTexture(bool selected) {
	if (selected) {
		sprite.setTexture(selectedTexture);
		_isSelected = true;
	}
	else {
		sprite.setTexture(texture);
		_isSelected = false;
	}
}

/*
* Change texture when button is selected for example
*/
void MyButton::changeTexture() {
	sprite.setTexture(selectedTexture);
	if (!_isSelected) {
		sound.play();
	}
	_isSelected = true;
}

//Setter and getters
void MyButton::setPosition(int x, int y)
{
	sprite.setPosition(x, y);
}

void MyButton::setToDo(int todo)
{
	_toDo = todo;
}

void MyButton::setVolume(int volume)
{
	if (volume >= 0 && volume <= 100) {
		sound.setVolume(volume);
	}
}

bool MyButton::isSelected(int x, int y)
{
	if (sprite.getGlobalBounds().contains(x, y)) {
		return true;
	}
	else if (_isSelected) {
		sprite.setTexture(texture);
		_isSelected = false;
		return false;
	}
	else {
		return false;
	}
}

sf::Sprite MyButton::getSprite() const
{
	return sf::Sprite(sprite);
}

int MyButton::getX() const
{
	return sprite.getPosition().x;
}

int MyButton::getY() const
{
	return sprite.getPosition().y;
}

int MyButton::toDo() const
{
	return _toDo;
}
