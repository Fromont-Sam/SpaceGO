#include "Panel.h"
#include "MyButton.h"
#include <sstream>
#pragma once
class Shop : public Panel
{
private:
	std::vector<MyButton*> cards;
	sf::Texture shop, star;
	sf::Sprite _shop, _star;
	sf::Font font;
	sf::Text _nbrStar;
	MyButton *back;
public:
	Shop(MyWindow* window);
	~Shop();
	void init();
	//Listeners
	int keyPressedOnce(sf::Keyboard::Key key);
	int mouseClicked(int x, int y, sf::Mouse::Button button);
	int mouseMove(int x, int y);
	//Getters
	int getType() const;
};

