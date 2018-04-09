#include "Panel.h"



Panel::Panel(MyWindow* window)
{
	mainWindow = window;
	if (!background.loadFromFile("images/background.png")) {};
	_background = sf::Sprite(background);
}

void Panel::moveBackground()
{
	_background.move(-0.5, 0);
	if (_background.getPosition().x == -1440) {
		_background.setPosition(0, 0);
	}
}

sf::Sprite Panel::getBackground() const
{
	return sf::Sprite(_background);
}

MyWindow* Panel::getWindow() const
{
	return mainWindow;
}
