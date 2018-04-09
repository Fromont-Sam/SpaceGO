#include "Panel.h"
#include "MyProgressBar.h"
#include "MyCheckbox.h"
#include "MyButton.h"
#pragma once
class Settings : public Panel
{
private:
	sf::Texture volume, music, vsync;
	sf::Sprite _volume, _music, _vsync;
	MyProgressBar *pbVolume;
	MyCheckbox *cbMusic, *cbVsync;
	MyButton *back;
public:
	Settings(MyWindow* window);
	~Settings();
	void init();
	//Listeners
	int keyPressedOnce(sf::Keyboard::Key key);
	int keyPressed(int key);
	int mouseMove(int x, int y);
	int mouseClicked(int x, int y, sf::Mouse::Button button);
	//Getters
	int getType() const;
};

