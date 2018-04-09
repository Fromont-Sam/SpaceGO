#include <SFML/Graphics.hpp>
#include "MyWindow.h"
#include <iostream>
#pragma once
class Panel
{
private:
	sf::Texture background;
	sf::Sprite _background;
	MyWindow* mainWindow;
public:
	Panel(MyWindow* window);
	enum {
		PANEL_SPLASHSCREEN,
		PANEL_MENU,
		PANEL_GAME,
		PANEL_SETTINGS,
		PANEL_SHOP,
		PANEL_SCORE,
		PANEL_ACCOUNT,
		PANEL_CREDITS
	};
	void moveBackground();
	virtual void blink() { return; };
	virtual void init() = 0;
	//Listeners
	virtual int keyPressed(int key) { return -1;  };
	virtual int keyPressedOnce(sf::Keyboard::Key key) { return -1; };
	virtual int mouseClicked(int x, int y, sf::Mouse::Button) { return -1; };
	virtual int mouseMove(int x, int y) { return -1; };
	//Getters
	virtual int getType() const = 0;
	MyWindow* getWindow() const;
	sf::Sprite getBackground() const;
};

