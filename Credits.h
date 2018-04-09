#include "Panel.h"
#include "MyButton.h"
#pragma once
class Credits : public Panel
{
private:
	sf::Text ln1, ln2, ln3;
	sf::Font font;
	MyButton back;
public:
	Credits(MyWindow* window);
	void init();
	//Listeners
	int keyPressedOnce(sf::Keyboard::Key key);
	int keyPressed(int key);
	int mouseMove(int x, int y);
	int mouseClicked(int x, int y, sf::Mouse::Button button);
	//Getters
	int getType() const;
};

