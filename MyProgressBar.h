#include <SFML/Graphics.hpp>
#pragma once
class MyProgressBar
{
private:
	float _percentage;
	int _start, _end;
	sf::Texture texture, rectTexture;
	sf::Sprite sprite, rectSprite;
public:
	MyProgressBar() {};
	MyProgressBar(std::string path);
	MyProgressBar(int start, int end, std::string path);
	~MyProgressBar();
	void setPosition(int x, int y);
	void setPositionBar(int x, int y);
	bool setPercentage(int x, int y);
	bool setPercentage(int percentage);
	//Getters
	int getPercentage() const;
	int getX() const;
	int getY() const;
	sf::Sprite getSprite() const;
	sf::Sprite getSpriteBar() const;
};

