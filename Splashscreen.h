#include "Panel.h"
#pragma once
class Splashscreen : public Panel
{
private:
	sf::Texture shadow, logo, button, buttonOff;
	sf::Sprite _shadow, _logo, _button;
public:
	Splashscreen(MyWindow* window);
	bool visible;
	void init();
	void blink();
	int keyPressedOnce(sf::Keyboard::Key key);
	int getType() const;
};

