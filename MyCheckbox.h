#include <SFML/Graphics.hpp>
#pragma once
class MyCheckbox
{
private:
	bool _checked;
	sf::Texture texture, checkTexture;
	sf::Sprite sprite;
public:
	MyCheckbox();
	~MyCheckbox();
	//Setters
	void setPosition(int x, int y);
	bool setChecked(int x, int y);
	void setChecked(bool checked);
	//Getters
	sf::Sprite getSprite() const;
	bool isChecked() const;
	int getX() const;
	int getY() const;
};

