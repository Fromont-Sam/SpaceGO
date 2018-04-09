#include "Splashscreen.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include "Menu.h"

Splashscreen::Splashscreen(MyWindow* window) : Panel(window) {


	//Init textures
	if (!shadow.loadFromFile("images/splashscreen/shadow.png")) {};
	if (!logo.loadFromFile("images/splashscreen/logo.png")) {};
	if (!button.loadFromFile("images/splashscreen/btn_keys.png")) {};
	if (!buttonOff.create(button.getSize().x , button.getSize().y)) {};


	//Init sprites
	_shadow = sf::Sprite(shadow);
	_logo = sf::Sprite(logo);
	_button = sf::Sprite(button);

	//Set sprites
	_logo.setPosition(433, 259);
	_button.setPosition(381, 670);
}

void Splashscreen::init()
{	
	getWindow()->clear();
	//Draw sprites
	getWindow()->draw(getBackground());
	getWindow()->draw(_shadow);
	getWindow()->draw(_logo);
	getWindow()->draw(_button);
}

void Splashscreen::blink()
{
	if(!visible) {
		_button.setTexture(button);
		visible = true;
	}
	else {
		_button.setTexture(buttonOff);
		visible = false;
	}
}

int Splashscreen::keyPressedOnce(sf::Keyboard::Key key)
{
	return Panel::PANEL_MENU;
}

int Splashscreen::getType() const {
	return Panel::PANEL_SPLASHSCREEN;
}
 