#include "Panel.h"
#include "MyButton.h"
#include <sstream>
#pragma once
class Account : public Panel
{
private:
	sf::Font font;
	sf::Text level, nbrStar;
	sf::Texture xp, star, selectedColor;
	sf::Sprite _xp, _star, _selectedColor;
	sf::RectangleShape rectXp;
	MyButton back;
	std::vector<MyButton> spaceships;
	std::vector<MyButton> colors;
public:
	Account(MyWindow* window);
	void init();
	//Listeners
	int keyPressedOnce(sf::Keyboard::Key key);
	int mouseMove(int x, int y);
	int mouseClicked(int x, int y, sf::Mouse::Button button);
	//Getters
	int getType() const;
};

