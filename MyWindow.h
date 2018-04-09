#include <SFML/Graphics.hpp>
#include "Config.h"
#pragma once
class MyWindow : public sf::RenderWindow
{
private :
	Config* config;
public:
	MyWindow(sf::VideoMode mode, std::string title, int style);
	~MyWindow();
	Config* getConfig() const;
};

