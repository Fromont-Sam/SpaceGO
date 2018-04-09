#include "MyWindow.h"

/*
* Constructor
*/
MyWindow::MyWindow(sf::VideoMode mode, std::string title, int style) : sf::RenderWindow(mode, title, style)
{
	config = new Config();
}

/*
* Destructor
*/
MyWindow::~MyWindow()
{
	delete config;
}

/*
* Get the current config
*/
Config * MyWindow::getConfig() const
{
	return config;
}
