#include "Panel.h"
#include "MyButton.h"
#include <SFML/Audio.hpp>
#pragma once
class Menu : public Panel
{
private:
	MyButton *btnPlay, *btnSettings, *btnScore, *btnShop, *btnAccount, *btnCredits;
public:
	Menu(MyWindow* window);
	~Menu();
	void init();
	//Listeners
	int mouseClicked(int x, int y, sf::Mouse::Button button);
	int mouseMove(int x, int y);
	//Getters
	int getType()  const;
};

